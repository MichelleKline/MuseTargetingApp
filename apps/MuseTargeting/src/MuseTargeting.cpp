//#include "MuseTargetingView.h"
#include "PseudoTGDriver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PseudoTGDriver p;
    p.show();

    //MuseTargetingView w;
    //w.show();


    return a.exec();
}
