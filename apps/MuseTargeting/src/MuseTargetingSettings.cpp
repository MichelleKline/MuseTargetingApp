// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "MuseTargetingSettings.h"

MuseTargetingSettings::MuseTargetingSettings(QWidget *parent) : QWidget(parent)
{
    // these are the default Muse System Settings
    // TO DO: allow to be defined using input file?
    MuseTargetingDOF psi("Psi", 0, 40, 0);
    m_museSettings.push_back(psi);
    MuseTargetingDOF theta("Theta",0, 360, 0);
    m_museSettings.push_back(theta);

    MuseTargetingDOF alpha("Alpha", -10, 10, 0);
    m_museSettings.push_back(alpha);
    MuseTargetingDOF LSlider("LSlider", 0, 40, 20);
    m_museSettings.push_back(LSlider);
    MuseTargetingDOF xTrolley("XTrolley", -20, 20, 0);
    m_museSettings.push_back(xTrolley);
    MuseTargetingDOF zTrolley("ZTrolley", -20, 20, 0);
    m_museSettings.push_back(zTrolley);

}

void MuseTargetingSettings::addSetting(QString name, double min, double max, double value){
    MuseTargetingDOF DOF(name, min, max, value);
    m_museSettings.push_back(DOF);
}

void MuseTargetingSettings::addSetting(QString name, double min, double max){
    MuseTargetingDOF DOF(name, min, max);
    m_museSettings.push_back(DOF);
}

void MuseTargetingSettings::setValue(QString settingName, double val){
    for (unsigned i = 0; i < m_museSettings.size(); ++i)
    {
        if (!m_museSettings[i].getName().compare(settingName)){
            m_museSettings[i].setValue(val);
            return;
        }
    }
}

std::vector<MuseTargetingDOF> MuseTargetingSettings::getSettings(){
    return m_museSettings;
}

double MuseTargetingSettings::getSettingMin(QString settingName){
    for (unsigned i = 0; i < m_museSettings.size(); ++i)
    {
        if (!m_museSettings[i].getName().compare(settingName))
            return m_museSettings[i].getMin();
    }
    return -999;  // MMK fixme - what to return if no match found?
}

double MuseTargetingSettings::getSettingMax(QString settingName){
    for (unsigned i = 0; i < m_museSettings.size(); ++i)
    {
        if (!m_museSettings[i].getName().compare(settingName))
            return m_museSettings[i].getMax();
    }
    return -999;  // MMK fixme - what to return if no match found?
}

double MuseTargetingSettings::getSettingValue(QString settingName){
    for (unsigned i = 0; i < m_museSettings.size(); ++i)
    {
        QString temp = m_museSettings[i].getName();
        if (!m_museSettings[i].getName().compare(settingName)){
            return m_museSettings[i].getValue();
        }
    }
    return -999;  // MMK fixme - what to return if no match found?
}

