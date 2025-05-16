#include "hexagoncontroller.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

HexagonController::HexagonController(MainWindow* mainWindow, QGraphicsScene* scene)
    : mainWindow(mainWindow), scene(scene)
{
}

HexagonController::~HexagonController()
{
    delete scene;
    delete mainWindow;
}

void HexagonController::initializeBoard(const QString& boardFile)
{


    QFile file(boardFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QStringList lines;
        QTextStream in(&file);
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
                    createHexagon(x, y, ch);
                    col += 5;
                }
                else {
                    col++;
                }
            }
        }
    }
}

void HexagonController::createHexagon(qreal x, qreal y, QChar ch)
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

    if (ch == '1') {
        hexItem->setBrush(QColor(100, 255, 100));
    } else if (ch == '2') {
        hexItem->setBrush(QColor(255, 255, 100));
    } else if (ch == '#') {
        hexItem->setBrush(QColor(100, 100, 255));
    } else if (ch == '~') {
        hexItem->setBrush(QColor(255, 150, 200));
    } else {
        hexItem->setBrush(Qt::white);
    }

    hexItem->setPen(QPen(Qt::black, 1));
    scene->addItem(hexItem);

    Cell cell;
    cell.type = (ch == ' ') ? '\0' : ch.toLatin1();
    cell.occupied = (ch == '#' || ch == '~');
    cell.player = (ch == '1') ? 1 : (ch == '2') ? 2 : 0;
    QPointF scenePos(x + hexWidth/2, y + hexHeight/2);
    board[snapToGrid(scenePos)] = cell;
}

QColor HexagonController::getPlayerColor(int player) const
{
    if (player == 1) return QColor(224, 27, 36);
    if (player == 2) return QColor(39, 174, 96);
    return Qt::white;
}

void HexagonController::updateHexagonColor(QGraphicsPolygonItem* hexItem, int player)
{
    if (!hexItem) return;

    QColor baseColor = getPlayerColor(player);
    QLinearGradient gradient(hexItem->boundingRect().topLeft(),
                             hexItem->boundingRect().bottomRight());
    gradient.setColorAt(0, baseColor.lighter(120));
    gradient.setColorAt(1, baseColor.darker(120));
    hexItem->setBrush(gradient);


}

std::pair<int, int> HexagonController::snapToGrid(QPointF scenePos) const
{
    int x = static_cast<int>(scenePos.x());
    int y = static_cast<int>(scenePos.y());
    int gridX = (x / cellWidth) * cellWidth;
    int gridY = (y / cellHeight) * cellHeight;
    return {gridX, gridY};
}

void HexagonController::setCurrentPlayer(int player)
{
    currentPlayer = player;
}

void HexagonController::setAgentSelected(bool selected)
{
    agentSelected = selected;
}

void HexagonController::clearSelection()
{
    agentSelected = false;
}

bool HexagonController::handleHexagonClick(QPointF scenePos)
{
    if (!agentSelected) {
        QMessageBox::information(mainWindow, "No Agent Selected",
                                 "Please select an agent first.");
        return false;
    }

    std::pair<int, int> gridPos = snapToGrid(scenePos);
    int a = gridPos.first;
    int b = gridPos.second;
    auto it1 = board.find(gridPos);

    /*
    std::pair<int,int> grid1 = {a,b+1};
    auto it2 = board.find(grid1);

    std::pair<int,int> grid3 = {a+1, b};
    auto it3 = board.find(grid3);

    std::pair<int,int> grid4 = {a +1, b+1};
    auto it4 = board.find(grid4);*/

    if (it1 == board.end()) return false;

    Cell &cell = it1->second;

    if (cell.occupied) {
        QMessageBox::information(mainWindow, "Invalid Move",
                                 "This cell is already occupied.");
        return true;
    }

    if ((currentPlayer == 1 && cell.type != '1') ||
        (currentPlayer == 2 && cell.type != '2')) {
        QMessageBox::information(mainWindow, "Invalid Move",
                                 "You can only place agents on your own color cells.");
        return true;
    }


    QGraphicsPolygonItem* hexItem = nullptr;
    QList<QGraphicsItem*> items = scene->items(scenePos);
    for (QGraphicsItem* item : items) {
        hexItem = dynamic_cast<QGraphicsPolygonItem*>(item);
        if (hexItem) break;
    }

    if (!hexItem) return false;

    updateHexagonColor(hexItem, currentPlayer);

    cell.occupied = true;
    cell.player = currentPlayer;

    clearSelection();
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
    emit playerChanged(currentPlayer);

    return true;
}
