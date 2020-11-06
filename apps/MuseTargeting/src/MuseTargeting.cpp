// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

/**
* This application assists in physically positioning the Muse Targeting System transducer.
* The app is accessed via Thermoguide. The observed geometric focus is passed to the app, and the 
* user interactively enters the Muse System settings psi, theta, alpha, L-slider, X-trolley, and Z-trolley.
* The app then calculates the theoretical focus based on these settings, compares the theoretical focus to 
* the observed focus, and calibrates. The user may also interactively enter the desired geometric focus. The
* app then calculates possible Muse System settings that would achieve this desired focus.
* The calculations used in this app were taken from MuseTargeting, a Python script developed by Dylan Palomino, 
* Dennis Parker, Allison Payne, and Michelle Kline. University of Utah, Salt Lake City, Utah, USA.
*/
#include "PseudoTGDriver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /** 
    * This is a small app that acts as a stand-in for Thermoguide during testing and dev. It simply allows the 
      user to enter and observed focus and send it to the Muse Targeting application.
     */
    PseudoTGDriver p;
    p.show();

    return a.exec();
}
