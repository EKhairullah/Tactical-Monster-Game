#ifndef CHOOSEG_H
#define CHOOSEG_H

#include <QWidget>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class ChooseGround; }
QT_END_NAMESPACE

class ChooseGround : public QWidget
{
    Q_OBJECT

public:
    ChooseGround(QWidget *parent = nullptr);
    ~ChooseGround();
    void createHexagon(qreal x, qreal y, QChar ch, QGraphicsScene *);
    void loadHexGrid(const QString& filePath, QGraphicsScene* scene, QGraphicsView*);



private slots:
    void on_pushButton_clicked();

private:
    Ui::ChooseGround *ui;

    const qreal hexSize = 45.0;
    const qreal hexWidth = hexSize * 2;
    const qreal hexHeight = hexSize * qSqrt(3);

    QGraphicsScene *scene1, *scene2, *scene3, *scene4, *scene5,
        *scene6, *scene7, *scene8, *scene9;
};
#endif
