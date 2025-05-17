<<<<<<< HEAD

#include <QApplication>
#include "chooseground.h"

#include "widget.h"

#include <QApplication>
>>>>>>> b7aa7283b79fc4dde3174842c4a856bd939d4f3d

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChooseGround *c = new ChooseGround(nullptr);
    c->show();

    Widget w;
    w.show();

    return a.exec();
}
