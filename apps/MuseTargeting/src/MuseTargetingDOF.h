// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef MUSETARGETINGDOF_H
#define MUSETARGETINGDOF_H

#include <QWidget>

class MuseTargetingDOF {

public:
    /**
     * Constructor
     *
     * @param name Name of this degree of freedom, for example "Psi"
     * @param lowerLimit Minimum allowable value for this degree of freedom
     * @param upperLimit Minimum allowable value for this degree of freedom
     * @param value Current value for this degree of freedom
     */
    MuseTargetingDOF(QString name, double lowerLimit, double upperLimit, double value);

    /**
     * Constructor
     *
     * @param name Name of this degree of freedom, for example "Psi"
     * @param lowerLimit Minimum allowable value for this degree of freedom
     * @param upperLimit Minimum allowable value for this degree of freedom
     */
    MuseTargetingDOF(QString name, double lowerLimit, double upperLimit);

    /** Default constructor */
    MuseTargetingDOF();

    /** Destructor */
    ~MuseTargetingDOF() = default;

    /** Define (set up) this degree of freedom with name, min and max */
    void define(QString name, double lowerLimit, double upperLimit);
    void setName(QString name);
    void setMax(double upperLimit);
    void setMin(double lowerLimit);
    bool setValue(double value);

    QString getName();
    double getMax();
    double getMin();
    double getValue();

signals:

private:
    // MMK FIXME: check validity by checking range (0 - 0 == issue)? Or should controller check validity?
    QString m_name  = "undefined";
    double m_upperLimit = 0;
    double m_lowerLimit = 0;
    double m_value      = 0;
};

#endif // MUSETARGETINGDOF_H
