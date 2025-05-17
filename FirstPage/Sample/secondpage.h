#ifndef SECONDPAGE_H
#define SECONDPAGE_H

#include <QMainWindow>
#include <QSize>
#include <QPushButton>
namespace Ui {
class secondPage;
}

class secondPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit secondPage(QWidget *parent = nullptr);
    void startSecond();
    void styleButton(QPushButton *button);
    void start_button_clicked();
    ~secondPage();

private:
    Ui::secondPage *ui;
    QSize qsize();

private slots:
    void s_button_clicked();
};

#endif // SECONDPAGE_H
