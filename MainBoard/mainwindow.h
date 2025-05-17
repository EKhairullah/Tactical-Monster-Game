
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unordered_map>
#include <utility>
#include <functional>
#include <QGraphicsScene>
#include <QPushButton>
struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

struct Cell {
    char type;
    bool occupied;
    int player;
};


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QPolygonF createHexagon(qreal x, qreal y, qreal size);
    MainWindow(QWidget *parent = nullptr);
    void StartGame();
    std::pair<int, int> snapToGrid(QPointF scenePos);
    // bool eventFilter(QObject *obj, QEvent *event);
    void Change_button_state();
    ~MainWindow();

private slots:
    void on_Agent1_clicked();
    void on_Agent2_clicked();

private:
    QPushButton* selectedButton = nullptr;

private:

    QMap<std::pair<int, int>, QGraphicsTextItem*> cellTextItems;

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    const int cellWidth = 25;
    const int cellHeight =40;
    bool AgentSelected;
    QChar agentSelectedChar;
    int currentPlayer;
    bool eventFilter(QObject *obj, QEvent *event);

    std::unordered_map<std::pair<int, int>, Cell, pair_hash> board;
};

#endif // MAINWINDOW_H
