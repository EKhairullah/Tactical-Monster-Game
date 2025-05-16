#ifndef HEXAGONCONTROLLER_H
#define HEXAGONCONTROLLER_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QMap>
#include <QPointF>
#include <unordered_map>
#include <utility>

struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second)) << 1;
    }
};

struct Cell {
    char type = '\0';
    bool occupied = false;
    int player = 0;
};

class MainWindow;

class HexagonController : public QObject
{
    Q_OBJECT
public:
    explicit HexagonController(MainWindow* mainWindow, QGraphicsScene* scene);//constructor
    ~HexagonController();

    void initializeBoard(const QString& boardFile);
    void setCurrentPlayer(int player);
    void setAgentSelected(bool selected);
    void clearSelection();

    std::pair<int, int> snapToGrid(QPointF scenePos) const;
    bool handleHexagonClick(QPointF scenePos);

    const std::unordered_map<std::pair<int, int>, Cell, pair_hash>& getBoardState() const { return board; }

signals:
    void playerChanged(int newPlayer);

private:
    void createHexagon(qreal x, qreal y, QChar ch);
    void updateHexagonColor(QGraphicsPolygonItem* hexItem, int player);
    QColor getPlayerColor(int player) const;

    MainWindow* mainWindow;
    QGraphicsScene* scene;
    std::unordered_map<std::pair<int, int>, Cell, pair_hash> board;

    const qreal hexWidth = 80;
    const qreal hexHeight = 69.4;
    const int cellWidth = 10;
    const int cellHeight = 32;

    bool agentSelected = false;
    int currentPlayer = 1;
    QGraphicsPolygonItem* lastClickedItem = nullptr;
};

#endif
