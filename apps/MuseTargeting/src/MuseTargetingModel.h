#ifndef MUSETARGETINGMODEL_H
#define MUSETARGETINGMODEL_H

#include "MuseTargetingSettings.h"
#include "../../libs/libCore/Core/Maths/Vector3.h"
#include <vector>
#include <QWidget>

# define M_PI 3.14159265358979323846  /* pi */

class MuseTargetingModel : public QWidget
{
    Q_OBJECT
public:
    explicit MuseTargetingModel(QWidget *parent = nullptr);

    MuseTargetingSettings* getCurrentSettings() { return &m_currentSettings; }
    MuseTargetingSettings* getSuggestedSettings() { return &m_suggestedSettings; }
    core::Vector3 getObservedFocus() { return m_observedFocus; }
    core::Vector3 getCalibration() { return m_calibration; }
    core::Vector3 getTheoreticalFocus() { return m_theoreticalFocus; };
    core::Vector3 getDesiredFocus() { return m_desiredFocus; }

signals:
    void modelChangedSignal();

private slots:
    void updateCurrentSettings(MuseTargetingSettings *s);
    void updateDesiredFocus(core::Vector3 f);
    void calcTheoreticalFocus();
    void calcSuggestedSettings();
    
private:
    MuseTargetingSettings m_currentSettings;
    MuseTargetingSettings m_suggestedSettings;
    core::Vector3 m_observedFocus;
    core::Vector3 m_calibration;
    core::Vector3 m_theoreticalFocus;
    core::Vector3 m_desiredFocus;
    bool m_isCalibrated = false;

    double m_persistZ;            // MMK Python reuses initial ZTrolley on subsequent calcs...
    double m_persistX;            // MMK Python reuses initial XTrolley on subsequent calcs...
    bool m_isPersistSet = false;  // MMK

    /** other Muse System variables from MuseTargeting Python */
    double m_xFocus = 0.0;    // default focus of transducer?
    double m_yFocus = 0.0;    // default focus of transducer?
    double m_zFocus = 106.8;  // default focus of transducer?
    double m_Lnull  = 20.2;
    double m_xcent  = 0;
    double m_ycent  = -55;
    double m_zcent  = -1.0 * (m_zFocus + m_Lnull);

    /** Helper functions */
    double degreesToRadians(double deg){ return (deg * M_PI) / 180; }
    double radiansToDegrees(double rad){ return rad * 180.0 / M_PI; }
};

#endif // MUSETARGETINGMODEL_H
