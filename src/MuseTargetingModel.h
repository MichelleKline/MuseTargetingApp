// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef MUSETARGETINGMODEL_H
#define MUSETARGETINGMODEL_H

#include "MuseTargetingSettings.h"
#include "../libs/libCore/Core/Maths/Vector3.h"
#include "../libs/libCore/Core/Constants.h"
#include <QWidget>

/**
* @brief QWidget class to manage the data underlying the Muse Targeting app.
*
* The model constists of:
*  - the observed focus
*  - current Muse System settings
*  - the theoretical focus
*  - the calibration
*  - the desired focus
*  - suggested Muse System settings
* 
* Whenever current Muse System settings are updated, the theoretical focus is also updated. If the observed 
* focus is set, and calibration has not been calculated, then calibration will be performed (simply the difference
* between observed focus and theoretical focus).
* 
* Whenver the desired focus is updated, the suggested Muse System settings will be calculated.
* 
* Any change to the model result in sending a signal to the view.
*/
class MuseTargetingModel : public QWidget
{
    Q_OBJECT
public:
    /** Constructor. A QWidget pointer is passed implicitly */
    explicit MuseTargetingModel(QWidget *parent = nullptr);

    /** Destructor. */
    ~MuseTargetingModel();

    /** Returns MuseTargetingSettings object containing current settings */
    MuseTargetingSettings* getCurrentSettings() { return &m_currentSettings; }

    /** Returns MuseTargetingSettings object containing suggested settings */
    MuseTargetingSettings* getSuggestedSettings() { return &m_suggestedSettings; }

    core::Vector3 getObservedFocus() { return m_observedFocus; }
    core::Vector3 getCalibration() { return m_calibration; }
    core::Vector3 getTheoreticalFocus() { return m_theoreticalFocus; }
    core::Vector3 getDesiredFocus() { return m_desiredFocus; }

    /** Each setting is a MuseTargetingDOF object (degree of freedom). Each DOF has a min and max allowable value */
    double getCurrentSettingMin(QString name) { return m_currentSettings.getSettingMin(name); }
    double getCurrentSettingMax(QString name) { return m_currentSettings.getSettingMax(name); }

    /** Reset current and suggested settings, theoretical and desired focus, and calibration to default settings */
    void reset();

signals:
    void modelChangedSignal();

private slots:
    /** Receive observed focus from MuseTargetingView, update the model */
    void updateObservedFocus(core::Vector3 f);

    /** Receive current settings from MuseTargetingView, update the model */
    void updateCurrentSettings(MuseTargetingSettings *s);

    /** Receive desired focus from MuseTargetingView, update the model */
    void updateDesiredFocus(core::Vector3 f);
    
private:
    MuseTargetingSettings m_currentSettings;    // user-provided Muse System settings
    bool m_areCurrSettingsRegistered = false;
    core::Vector3 m_observedFocus;              // Thermoguide-provided observed focus
    bool m_isObservedFocusSet = false;
    core::Vector3 m_calibration;
    bool m_isCalibrated = false;
    core::Vector3 m_theoreticalFocus;
    core::Vector3 m_desiredFocus;
    MuseTargetingSettings m_suggestedSettings;
    
    /** One of the two main functions. Calculates suggested Muse System settings based on the desired focus. */
    void calcSuggestedSettings();

    /** One of the two main functions. Calculates the theoretical geometric focus, based on current Muse System settings. */
    void calcTheoreticalFocus();

    /** Simply computes the difference between the theoretical focus and the observed focus. */
    void calibrate();

    /** other Muse System variables from MuseTargeting Python */
    double m_xFocus = 0.0;    // default focus of transducer?
    double m_yFocus = 0.0;    // default focus of transducer?
    double m_zFocus = 106.8;  // default focus of transducer?
    double m_Lnull  = 20.2;
    double m_xcent  = 0;
    double m_ycent  = -55;
    double m_zcent  = -1.0 * (m_zFocus + m_Lnull);

    /** Helper functions */
    double degreesToRadians(double deg){ return (deg * core::IGT_PI) / 180; }
    double radiansToDegrees(double rad){ return rad * 180.0 / core::IGT_PI; }
};

#endif // MUSETARGETINGMODEL_H
