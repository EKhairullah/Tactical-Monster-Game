#ifndef WIDGET_H
#define WIDGET_H
// #include "mainwindow.h"
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QString first;
    QString last;
};
#endif
