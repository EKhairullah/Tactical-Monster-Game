
#include <QApplication>
#include "chooseground.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChooseGround *c = new ChooseGround(nullptr);
    c->show();
    return a.exec();
}
