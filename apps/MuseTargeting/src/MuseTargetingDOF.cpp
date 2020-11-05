// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "MuseTargetingDOF.h"

MuseTargetingDOF::MuseTargetingDOF(QString name, double lowerLimit, double upperLimit, double value){
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

void MuseTargetingDOF::define(QString name, double lowerLimit, double upperLimit){  //
    m_name = name;
    m_upperLimit = upperLimit;
    m_lowerLimit = lowerLimit;
}

void MuseTargetingDOF::setName(QString name){
    m_name = name;
}

void MuseTargetingDOF::setMax(double upperLimit){
    m_upperLimit = upperLimit;
}

void MuseTargetingDOF::setMin(double lowerLimit){
    m_lowerLimit =lowerLimit;
}

bool MuseTargetingDOF::setValue(double value){
    // MMK FIXME:  maybe it is up to controller to check this
    // If this DOF is a suggested setting, we allow it to be out of range
//    if ((value < m_lowerLimit) || (value > m_upperLimit))
//        return false;
//    else {
        m_value = value;
        return true;
//    }
}

QString MuseTargetingDOF::getName(){
    return m_name;
}

double MuseTargetingDOF::getMax(){
    return m_upperLimit;
}

double MuseTargetingDOF::getMin(){
    return m_lowerLimit;
}

double MuseTargetingDOF::getValue(){
    return m_value;
}
