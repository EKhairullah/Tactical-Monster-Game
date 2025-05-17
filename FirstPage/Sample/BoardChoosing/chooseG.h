#ifndef CHOOSEG_H
#define CHOOSEG_H

#include <QWidget>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void createHexagon(qreal x, qreal y, QChar ch, QGraphicsScene *);
    void loadHexGrid(const QString& filePath, QGraphicsScene* scene, QGraphicsView*);

private:
    Ui::Widget *ui;

    // Hexagon dimensions
    const qreal hexSize = 40.0;
    const qreal hexWidth = hexSize * 2;
    const qreal hexHeight = hexSize * qSqrt(3);

    QGraphicsScene *scene1, *scene2, *scene3, *scene4, *scene5,
        *scene6, *scene7, *scene8, *scene9;
};
#endif // CHOOSEG_H
