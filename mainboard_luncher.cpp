// mainboard_launcher.cpp
#include <QApplication>
#include "chooseground.h"

void launchMainBoard() {
    ChooseGround *c = new ChooseGround(nullptr);
    c->show();
}
