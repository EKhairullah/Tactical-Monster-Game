
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <utility>
#include <QGraphicsScene>
#include <QPushButton>
#include "hexagoncontroller.h"



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
    MainWindow(QWidget *parent = nullptr, int m =0);
    void StartGame();
    std::pair<int, int> snapToGrid(QPointF scenePos);
    // bool eventFilter(QObject *obj, QEvent *event);
    void Change_button_state();
    ~MainWindow();
    void onPlayerChanged(int newPlayer);
    static int address;

private slots:
    void on_Agent1_clicked();

    void on_Agent2_clicked();

private:
    QPushButton* selectedButton = nullptr;

private:
    HexagonController* hexController;

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    const int cellWidth = 10;
    const int cellHeight =32;
    bool AgentSelected;
    QChar agentSelectedChar;
    int currentPlayer;
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // MAINWINDOW_H
