// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include <QWidget>
#include "ui_PseudoTGDriver.h"
#include "../../libs/libCore/Core/Maths/Vector3.h"
#include "MuseTargetingView.h"

/**
* Small app to act as a stand-in for Thermoguide during testing and dev. Allows user to
* send observed focus to Muse Targeting app.
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
