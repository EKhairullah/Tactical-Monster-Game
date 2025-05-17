#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QGraphicsTextItem>
#include <QTextStream>
#include <QMouseEvent>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentPlayer = 1;

    // Set initial UI state
    ui->Agent1->setDisabled(false);
    ui->Agent2->setDisabled(true);
    ui->Frame1->setHidden(true);
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
    color: rgb(224, 27, 36);
    background-color: transparent;
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


    QFile file(":/boards/grids/grid8.txt");

    QGraphicsScene *scene = new QGraphicsScene(this);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        int row = 0;

        while (!in.atEnd()) {
            line = in.readLine();

            for (int col = 0; col < line.length(); ++col) {
                QChar ch = line[col];
                QString chStr(ch);

                QGraphicsTextItem *textItem = scene->addText(chStr);
                if(chStr != '1' && chStr != '2' && chStr != '~' && chStr != '#') textItem->setHtml(QString("<span style='color: rgb(0, 255, 0);'>%1</span>").arg(chStr));
                textItem->setFont(QFont("Courier", 16));

                int sceneX = col * this->cellWidth;
                int sceneY = row * this->cellHeight;
                textItem->setPos(sceneX, sceneY);


                if (ch == '1' || ch == '2' || ch == '~' || ch == '#') {

                    Cell cell;
                    cell.type = ch.toLatin1();
                    cell.occupied = ((ch == '#' || ch == '~') ? true : false);
                    if(ch == '1' || ch == '2') cell.player = (ch == '1') ? 1 : 2;
                    else cell.player = 0;  // not a place to drag things
                    QPointF scenePos(sceneX, sceneY);
                    board[snapToGrid(scenePos)] = cell;
                    if(ch == '1' || ch == '2') textItem->setHtml(QString("<span style='color: rgb(255, 25, 255);'>%1</span>").arg(chStr));
                    else textItem->setHtml(QString("<span style='color: rgb(255, 215, 0);'>%1</span>").arg(chStr));
                }
            }
            ++row;
        }

        file.close();
    }

    ui->graphicsView->setScene(scene);
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
        AgentSelected = false;
        agentSelectedChar = '\0';
        return;
    }

    if (selectedButton) {
        selectedButton->setChecked(false);
    }

    clickedButton->setChecked(true);
    selectedButton = clickedButton;
    AgentSelected = true;
    agentSelectedChar = clickedButton->text().at(0);
}


void MainWindow::StartGame()
{
    disconnect(ui->Agent1, &QPushButton::clicked, this, &MainWindow::on_Agent1_clicked);
    disconnect(ui->Agent2, &QPushButton::clicked, this, &MainWindow::on_Agent2_clicked);

    QList<QPushButton*> buttons = {
        ui->button11, ui->button21, ui->button31, ui->button41,
        ui->button12, ui->button22, ui->button32, ui->button42
    };

    for (QPushButton* button : buttons) {
        connect(button, &QPushButton::clicked, this, &MainWindow::Change_button_state);
    }
    // connect(ui->Agent1, &QPushButton::clicked, this, &MainWindow::on_Agent1_clicked);
    // connect(ui->Agent2, &QPushButton::clicked, this, &MainWindow::on_Agent2_clicked);

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
    // Only allow interaction if it's player 2's turn
    if(currentPlayer != 2) return;

    ui->Frame2->setHidden(!ui->Frame2->isHidden());
    // Hide player 1's frame if showing
    if(!ui->Frame1->isHidden()) ui->Frame1->setHidden(true);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if(currentPlayer == 1) {
        ui->Agent1->setDisabled(false);
        ui->Agent2->setDisabled(true);
        ui->Frame2->setHidden(true);
    } else {
        ui->Agent1->setDisabled(true);
        ui->Agent2->setDisabled(false);
        ui->Frame1->setHidden(true);
    }


    if (obj == ui->graphicsView->viewport() && event->type() == QEvent::MouseButtonPress) {
        if (!this->AgentSelected) return false; // No agent selected yet

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());

        std::pair<int, int> gridPos = snapToGrid(scenePos);
        QPointF snappedScenePos(gridPos.first, gridPos.second);

        auto it = board.find(gridPos);
        if (it == board.end()) return false;

        Cell &cell = it->second;

        // Validation: Check for occupancy and correct cell type for the current player
        if (cell.occupied) {
            QMessageBox msgBox;
            msgBox.setText("Cell aready occupied.");
            msgBox.exec();
            // qDebug() << "Cell already occupied.";
            return true;
        }
        if ((currentPlayer == 1 && cell.type != '1') || (currentPlayer == 2 && cell.type != '2')) {
            qDebug() << "Invalid move for current player.";
            QMessageBox msgBox;
            msgBox.setText("Invalid move for current player.");
            msgBox.exec();
            return true;
        }

        // Remove previous character (if exists) from this grid cell
        if (cellTextItems.contains(gridPos)) {
            QGraphicsTextItem* oldItem = cellTextItems[gridPos];
            if (oldItem) {
                ui->graphicsView->scene()->removeItem(oldItem);
                delete oldItem;
            }
            cellTextItems.remove(gridPos);
        }

        // Place new character for the agent
        QGraphicsTextItem *item = ui->graphicsView->scene()->addText(QString(agentSelectedChar));
        item->setFont(QFont("Courier", 18));
        item->setDefaultTextColor(Qt::blue); // Optional: Color based on player
        item->setPos(snappedScenePos);

        // Track the item for future removal
        cellTextItems[gridPos] = item;

        // Update logic
        cell.occupied = true;
        cell.player = currentPlayer;

        AgentSelected = false;
        agentSelectedChar = '\0';
        currentPlayer = (currentPlayer == 1) ? 2 : 1;

        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

