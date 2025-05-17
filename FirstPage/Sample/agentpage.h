#ifndef AGENTPAGE_H
#define AGENTPAGE_H
// #include "chooseground.h"
// #include "hexagoncontroller.h"

#include <QMainWindow>

namespace Ui {
class agentPage;
}

class agentPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit agentPage(QWidget *parent = nullptr);
    ~agentPage();

private slots:
    void on_backButton_clicked();

private:
    Ui::agentPage *ui;
    QWidget *m_previousWindow = nullptr;
};

#endif
