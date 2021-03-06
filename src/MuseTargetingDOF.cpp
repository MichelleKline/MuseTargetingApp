// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "MuseTargetingDOF.h"

MuseTargetingDOF::MuseTargetingDOF(QString name, double lowerLimit, double upperLimit, double value) {
    m_name = name;
    m_lowerLimit = lowerLimit;
    m_upperLimit = upperLimit;
    m_value = value;
}

MuseTargetingDOF::MuseTargetingDOF(QString name, double lowerLimit, double upperLimit) {
    m_name = name;
    m_lowerLimit = lowerLimit;
    m_upperLimit = upperLimit;
}

MuseTargetingDOF::MuseTargetingDOF(){} // keep default values

void MuseTargetingDOF::define(QString name, double lowerLimit, double upperLimit) {  
    m_name = name;
    m_upperLimit = upperLimit;
    m_lowerLimit = lowerLimit;
}
