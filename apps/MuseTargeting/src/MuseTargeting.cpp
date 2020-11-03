#include "MuseTargetingView.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MuseTargetingView w;
    w.show();
    return a.exec();
}
