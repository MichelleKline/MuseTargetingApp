// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef MUSETARGETINGVIEW_H
#define MUSETARGETINGVIEW_H

#include <QtWidgets/QWidget>
#include "ui_MuseTargetingView.h"
#include "MuseTargetingModel.h"
#include "MuseTargetingSettings.h"
#include "../../libs/libCore/Core/Maths/Vector3.h"

/**
* @brief QWidget class to display and manage the Muse Targeting window.
* 
* This widget consists of one window, with widgets to:
*  - display the observed focus (read-only, sent from Thermoguide)
*  - allow user to interactively enter the Muse System settings,
*  - display the theoretical focus (temporary, during testing and dev)
*  - display the calibration (temporary, during testing and dev)
*  - allow user to interactively enter the desired focus
*  - display suggested Muse System settings based on the desired focus and calibration.
*/
class MuseTargetingView : public QWidget
{
    Q_OBJECT

public:
    /** Constructor. QWidget object pointer is implicitely passed */
    MuseTargetingView(QWidget* parent = nullptr);

    /** Destructor. */
    ~MuseTargetingView();

private slots:
    /** This captures the signal automatically generated by the "Enter" button click. */
    void enterButtonClicked();

    /** 
    * Captures signal from MuseTargetingModel indicating that the model has changed. 
    * Simply displays all model data in the widgets.
    */
    void refreshView();

    /** Captures the signal automatically generated by the "Calculate" button click. */
    void calculateButtonClicked();

    /** This button might be temporary - during testing and dev. */
    void resetButtonClicked();

    /** Captures signal sent by Thermoguide indicating that the observed focus is updated. */
    void receiveObservedFocus(core::Vector3 of);

signals:
    /** Sends signal containing values from current settings widgets to MuseTargetingView */
    void updateCurrentSettings(MuseTargetingSettings* s);

    /** Sends signal containing values from desired focus widgets to MuseTargetingView */
    void updateDesiredFocus(core::Vector3 df);

    /** Sends signal containing values from observed focus widgets to MuseTargetingView */
    void sendObservedFocus(core::Vector3 of);

private:
    Ui::MuseTargetingViewClass ui;
    MuseTargetingModel m_model;

    /** Helper function to display QMessageBox when user has entered an invalid value in the current settings widgets. */
    void invalidMessage(QString settingName);
};
#endif // MUSETARGETINGVIEW_H
