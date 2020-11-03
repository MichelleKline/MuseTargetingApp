// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef MUSETARGETINGSETTINGS_H
#define MUSETARGETINGSETTINGS_H

#include "MuseTargetingDOF.h"
#include <QWidget>
#include <vector>

/**
* @brief Model class for Muse Targeting. Stores degrees of freedom for Muse System.
*/
class MuseTargetingSettings : public QWidget
{
    Q_OBJECT
public:
    /** Default constructor */
    explicit MuseTargetingSettings(QWidget *parent = nullptr);
    //    MuseTargetingSettings(std::vector<std::string> DOFNames,std::vector<double> DOFMinLimits, std::vector<double> DOFMaxLimits);
    //    MuseTargetingSettings(std::vector<std::string> DOFNames,std::vector<double> DOFMinLimits, std::vector<double> DOFMaxLimits, std::vector<double>DOFValues);

    /** Destructor */
    ~MuseTargetingSettings(){};

    /** Add a degree of freedom to the stored vector of degrees of freedom */
    void addSetting(QString name, double min, double max, double value);
    void addSetting(QString name, double min, double max);

    /** update the value of thie degree of freedom */
    void setValue(QString settingName, double val);

    /** Return all of the degrees of freedom defined for this settings object */
    std::vector<MuseTargetingDOF> getSettings();
    /** The minimum allowable value for this degree of freedom */
    double getSettingMin(QString settingName);
    /** The maximum allowable value for this degree of freedom */
    double getSettingMax(QString settingName);
    /** The current value for this degree of freedom */
    double getSettingValue(QString settingName);

    size_t getNumSettings(){ return m_museSettings.size(); }

    // MMK need check to ensure that no duplication of setting name
    // MMK how to handle value that is not >= min and <= max
    // MMK how to handle min > max

public slots:
    //void testSlot(int n);

signals:
    //    bool emitSignalWhenChanged();

private:
    /** This is the vector of degrees of freedom that describe this settings object */
    std::vector<MuseTargetingDOF> m_museSettings;
};

#endif // MUSETARGETINGSETTINGS_H
