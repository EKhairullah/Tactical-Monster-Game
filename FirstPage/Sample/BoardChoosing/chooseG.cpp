#include "chooseG.h"
#include "ui_chooseG.h"
#include "hexagone.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    scene1 = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    scene3 = new QGraphicsScene(this);
    scene4 = new QGraphicsScene(this);
    scene5 = new QGraphicsScene(this);
    scene6 = new QGraphicsScene(this);
    scene7 = new QGraphicsScene(this);
    scene8 = new QGraphicsScene(this);


    // Assign scenes to views
    ui->graphicsView1->setScene(scene1);
    ui->graphicsView2->setScene(scene2);
    ui->graphicsView3->setScene(scene3);
    ui->graphicsView4->setScene(scene4);
    ui->graphicsView5->setScene(scene5);
    ui->graphicsView6->setScene(scene6);
    ui->graphicsView7->setScene(scene7);
    ui->graphicsView8->setScene(scene8);


    // Load grid into first view
    loadHexGrid(":/grids/grid1.txt", scene1, ui->graphicsView1);
    loadHexGrid(":/grids/grid2.txt", scene2, ui->graphicsView2);
    loadHexGrid(":/grids/grid3.txt", scene3, ui->graphicsView3);
    loadHexGrid(":/grids/grid4.txt", scene4, ui->graphicsView4);
    loadHexGrid(":/grids/grid5.txt", scene5, ui->graphicsView5);
    loadHexGrid(":/grids/grid6.txt", scene6, ui->graphicsView6);
    loadHexGrid(":/grids/grid7.txt", scene7, ui->graphicsView7);
    loadHexGrid(":/grids/grid8.txt", scene8, ui->graphicsView8);

}

void Widget::loadHexGrid(const QString& filePath, QGraphicsScene* scene, QGraphicsView *view)
{
    scene->clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines << in.readLine();
    }
    file.close();

    for (int row = 0; row < lines.size()-1; row++) {
        const QString &line = lines[row];
        for (int col = 0; col < line.length()-1; ) {
            if (line[col] == '/') {
                QChar ch = line[col+1];
                if (ch == '\\' || ch == '_' || ch == '|') {
                    col += 2;
                    continue;
                }

                qreal x = (col / 6.0) * hexWidth * 1.5;
                qreal y = row * hexHeight * 0.5;
                createHexagon(x, y, ch, scene);
                col += 5;
            }
            else {
                col++;
            }
        }
    }

    // Adjust view to fit content
    if (!scene->items().empty()) {
        view->fitInView(scene->itemsBoundingRect().adjusted(-20, -20, 20, 20),
                                     Qt::KeepAspectRatio);
    }
    view->scale(6,6);
}
void Widget::createHexagon(qreal x, qreal y, QChar ch, QGraphicsScene *scene)
{
    QPolygonF hexagon;
    hexagon << QPointF(hexWidth*0.25, 0)
            << QPointF(hexWidth*0.75, 0)
            << QPointF(hexWidth, hexHeight*0.5)
            << QPointF(hexWidth*0.75, hexHeight)
            << QPointF(hexWidth*0.25, hexHeight)
            << QPointF(0, hexHeight*0.5);

    QGraphicsPolygonItem *hexItem = new QGraphicsPolygonItem(hexagon);
    hexItem->setPos(x, y);

    // Set initial color based on content
    if (ch == '1') {
        hexItem->setBrush(QColor(100, 255, 100)); // Light green
    } else if (ch == '2') {
        hexItem->setBrush(QColor(255, 255, 100)); // Yellow
    } else if (ch == '#') {
        hexItem->setBrush(QColor(100, 100, 255)); // Blue
    } else if (ch == '~') {
        hexItem->setBrush(QColor(255, 150, 200)); // Pink
    } else {
        hexItem->setBrush(Qt::white); // Empty
    }

    hexItem->setPen(QPen(Qt::black, 1));
    scene->addItem(hexItem);
}
Widget::~Widget()
{
    delete ui;
}
