// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "PseudoTGDriver.h"

/** 
* Constructor. Builds the small pseudoTGDriver app.
* *
* @param parent QWidget parent object.
*/
PseudoTGDriver::PseudoTGDriver(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    mtView.show();
    
    connect(ui.pseudoTGSendButton, SIGNAL(clicked()), this, SLOT(sendButtonClicked()));
    connect(this, SIGNAL(sendObservedFocus(core::Vector3)), &mtView, SLOT(receiveObservedFocus(core::Vector3)));
}

/** Destructor */
PseudoTGDriver::~PseudoTGDriver()
{}

/** When user clicks the send button, get the observed focus from the edit widgets, then send to MuseTargetingView */
void PseudoTGDriver::sendButtonClicked() {
    // get desired focus from ui
    QString observedXString = ui.pseudoTGObservedXEdit->toPlainText();
    QString observedYString = ui.pseudoTGObservedYEdit->toPlainText();
    QString observedZString = ui.pseudoTGObservedZEdit->toPlainText();
    core::Vector3 of;
    of.x() = observedXString.toDouble();
    of.y() = observedYString.toDouble();
    of.z() = observedZString.toDouble();

    emit sendObservedFocus(of);
}