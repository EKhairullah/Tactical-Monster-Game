#include "agentpage.h"
#include "ui_agentpage.h"
#include "secondpage.h"
agentPage::agentPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::agentPage),
    m_previousWindow(parent)
{
    ui->setupUi(this);
    ui->backButton->setStyleSheet(
        "QPushButton {"
        "   color: green;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ff512f, stop:1 #dd2476);"
        "   border-radius: 8px;"
        "   padding: 5px 10px;"
        "   border: 1px solid #ffffff;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #dd2476, stop:1 #ff512f);"
        "}"
        "QPushButton:pressed {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #cc1c66, stop:1 #ee4025);"
        "}"
        );
}

agentPage::~agentPage()
{
    delete ui;
}



void agentPage::on_backButton_clicked()
{
    hide();
    secondPage *s = new secondPage(nullptr);
    s->setAttribute(Qt::WA_DeleteOnClose);
    s->resize(70,700);
    s->show();
}

