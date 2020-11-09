// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include <QWidget>
#include "ui_PseudoTGDriver.h"
#include "../libs/libCore/Core/Maths/Vector3.h"
#include "MuseTargetingView.h"

/**
* Qwidget class to display a single window to act as a stand-in for Thermoguide during testing and dev. 
* *
* This window allows user to enter observed focus x, y, and z, and to click a button which will send
* the observed focus to Muse Targeting window.
*/
class PseudoTGDriver : public QWidget
{
	Q_OBJECT

public:
	PseudoTGDriver(QWidget *parent = Q_NULLPTR);
	~PseudoTGDriver();

private slots:
	void sendButtonClicked();

signals:
	void sendObservedFocus(core::Vector3 of);

private:
	Ui::PseudoTGDriver ui;
	MuseTargetingView mtView;
};
