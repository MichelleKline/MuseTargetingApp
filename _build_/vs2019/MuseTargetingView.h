#pragma once

#include <QtWidgets/QWidget>
#include "ui_MuseTargetingView.h"

class MuseTargetingView : public QWidget
{
    Q_OBJECT

public:
    MuseTargetingView(QWidget *parent = Q_NULLPTR);

private:
    Ui::MuseTargetingViewClass ui;
};
