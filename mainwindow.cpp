#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QGraphicsTextItem>
#include <QTextStream>
#include <QMouseEvent>
#include <QMessageBox>
#include <QRegularExpression>

int MainWindow::address = 1;

MainWindow::MainWindow(QWidget *parent, int i)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->address = i;
    currentPlayer = 1;
    ui->player1->setText("Ali Ahmad");
    ui->player2->setText("Abbas Ahmadi");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    hexController = new HexagonController(this, scene);

    ui->Agent1->setDisabled(false);
    ui->Agent2->setDisabled(true);
    ui->Frame1->setHidden(false);
    ui->Frame2->setHidden(true);

    ui->graphicsView->viewport()->installEventFilter(this);

    ui->Agent1->setStyleSheet(R"(
    QPushButton {
        color: rgb(224, 27, 36);
        background-color: transparent;
        border: 2px solid rgb(224, 27, 36);
        border-radius: 8px;
        padding: 6px 12px;
        font-weight: bold;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: rgba(224, 27, 36, 0.1);
        color: white;
        border: 2px solid white;
    }
    QPushButton:pressed {
        background-color: rgb(224, 27, 36);
        color: white;
        border: 2px solid rgb(224, 27, 36);
    }
)");


    QString redStyle = R"(
QPushButton {
    background-color: black;
    color: rgb(224, 27, 36);
    border: 2px solid rgb(224, 27, 36);
    border-radius: 8px;
    padding: 6px 12px;
    font-weight: bold;
    font-size: 14px;
    transition: all 0.2s ease-in-out;
}

QPushButton:hover {
    background-color: rgba(224, 27, 36, 0.1);
    color: white;
    border: 2px solid white;
    box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.2); /* subtle shadow */
}

QPushButton:pressed {
    background-color: rgb(200, 20, 30);
    color: white;
    border: 2px solid rgb(224, 27, 36);
}

QPushButton:checked {
    background-color: rgb(224, 27, 36);
    color: white;
    border: 2px solid white;
    font-weight: bold;
}
)";

    ui->button11->setStyleSheet(redStyle);
    ui->button21->setStyleSheet(redStyle);
    ui->button31->setStyleSheet(redStyle);
    ui->button41->setStyleSheet(redStyle);

    ui->button11->setCheckable(true);
    ui->button21->setCheckable(true);
    ui->button31->setCheckable(true);
    ui->button41->setCheckable(true);

    ui->Agent2->setStyleSheet(R"(
QPushButton {
    color: rgb(39, 174, 96);
    background-color: transparent;
    border: 2px solid rgb(39, 174, 96);
    border-radius: 8px;
    padding: 6px 12px;
    font-weight: bold;
    font-size: 14px;
}
QPushButton:hover {
    background-color: rgba(39, 174, 96, 0.1);
    color: white;
    border: 2px solid white;
}
QPushButton:pressed {
    background-color: rgb(39, 174, 96);
    color: white;
    border: 2px solid rgb(39, 174, 96);
}
)");

    QString greenStyle = R"(
QPushButton {
    color: rgb(39, 174, 96);
    background-color: transparent;
    border: 2px solid rgb(39, 174, 96);
    border-radius: 8px;
    padding: 6px 12px;
    font-weight: bold;
    font-size: 14px;
    transition: all 0.2s ease-in-out;
}
QPushButton:hover {
    background-color: rgba(39, 174, 96, 0.1);
    color: white;
    border: 2px solid white;
    box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.2);
}
QPushButton:pressed {
    background-color: rgb(33, 150, 83);
    color: white;
    border: 2px solid rgb(39, 174, 96);
}
QPushButton:checked {
    background-color: rgb(39, 174, 96);
    color: white;
    border: 2px solid white;
    font-weight: bold;
}
)";

    ui->button12->setCheckable(true);
    ui->button22->setCheckable(true);
    ui->button32->setCheckable(true);
    ui->button42->setCheckable(true);

    ui->button12->setStyleSheet(greenStyle);
    ui->button22->setStyleSheet(greenStyle);
    ui->button32->setStyleSheet(greenStyle);
    ui->button42->setStyleSheet(greenStyle);

    qDebug() << this->address << " ";

    if(this->address == 1)     hexController->initializeBoard(":/boards/grids/grid1.txt");
    else if(address == 2) hexController->initializeBoard(":/boards/grids/grid2.txt");
    else if(address == 3) hexController->initializeBoard(":/boards/grids/grid3.txt");
    else if(address == 4) hexController->initializeBoard(":/boards/grids/grid4.txt");
    else if(address == 5) hexController->initializeBoard(":/boards/grids/grid5.txt");
    else if(address == 6) hexController->initializeBoard(":/boards/grids/grid6.txt");
    else if(address == 7) hexController->initializeBoard(":/boards/grids/grid7.txt");
    else if(address == 8) hexController->initializeBoard(":/boards/grids/grid8.txt");
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView->scale(17, 17);


    connect(hexController, &HexagonController::playerChanged,
            this, &MainWindow::onPlayerChanged);

    StartGame();
}



std::pair<int, int> MainWindow::snapToGrid(QPointF scenePos) {
    int x = static_cast<int>(scenePos.x());
    int y = static_cast<int>(scenePos.y());
    int gridX = (x / cellWidth) * cellWidth;
    int gridY = (y / cellHeight) * cellHeight;
    return {gridX, gridY};
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Change_button_state()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    if (selectedButton == clickedButton) {
        clickedButton->setChecked(false);
        selectedButton = nullptr;
        hexController->clearSelection();
        return;
    }

    if (selectedButton) {
        selectedButton->setChecked(false);
    }

    clickedButton->setChecked(true);
    selectedButton = clickedButton;
    hexController->setAgentSelected(true);
}


void MainWindow::StartGame()
{

    QList<QPushButton*> buttons = {
        ui->button11, ui->button21, ui->button31, ui->button41,
        ui->button12, ui->button22, ui->button32, ui->button42
    };

    for (QPushButton* button : buttons) {
        connect(button, &QPushButton::clicked, this, &MainWindow::Change_button_state);
    }

}

void MainWindow::on_Agent1_clicked()
{
    qDebug() << "Agent1 clicked - current player:" << currentPlayer;
    qDebug() << "Frame1 visibility before:" << !ui->Frame1->isHidden();

    if(currentPlayer != 1) {
        qDebug() << "Not player 1's turn, ignoring click";
        return;
    }

    ui->Frame1->setHidden(!ui->Frame1->isHidden());
    if(!ui->Frame2->isHidden()) {
        qDebug() << "Hiding Frame2 as it was visible";
        ui->Frame2->setHidden(true);
    }

    qDebug() << "Frame1 visibility after:" << !ui->Frame1->isHidden();
}


void MainWindow::on_Agent2_clicked()
{
    if(currentPlayer != 2) return;

    ui->Frame2->setHidden(!ui->Frame2->isHidden());
    if(!ui->Frame1->isHidden()) ui->Frame1->setHidden(true);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->graphicsView->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());
        return hexController->handleHexagonClick(scenePos);
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::onPlayerChanged(int newPlayer)
{
    currentPlayer = newPlayer;

    if (currentPlayer == 1) {
        ui->Agent1->setDisabled(false);
        ui->Agent2->setDisabled(true);
        ui->Frame1->setHidden(false);
        ui->Frame2->setHidden(true);
    } else {
        ui->Agent1->setDisabled(true);
        ui->Agent2->setDisabled(false);
        ui->Frame1->setHidden(true);
        ui->Frame2->setHidden(false);
    }

    if (selectedButton) {
        selectedButton->setChecked(false);
        selectedButton = nullptr;
    }
}
