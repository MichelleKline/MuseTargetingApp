#pragma once

#include <QWidget>
#include "ui_PseudoTGDriver.h"
#include "../../libs/libCore/Core/Maths/Vector3.h"
#include "MuseTargetingView.h"

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
