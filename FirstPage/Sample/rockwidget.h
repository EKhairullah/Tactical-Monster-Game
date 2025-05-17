#ifndef ROCKWIDGET_H
#define ROCKWIDGET_H

#include <QWidget>

class RockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RockWidget(QWidget *parent = nullptr);

private:
    QSize qsize();
    void Start();
private slots:
    void button_clicked();

};

#endif // ROCKWIDGET_H
