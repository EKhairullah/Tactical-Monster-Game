#include <QApplication>
#include "rockwidget.h"
#include <chooseground.h>
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // MainWindow w;
    // w.setWindowTitle("My Main Window");
    // w.show();
    RockWidget r;
    
    ChooseGround m;
    m.show();
    r.resize(700, 600);
    r.setWindowTitle("Rock Widget");
    r.show();

    return app.exec();
}
