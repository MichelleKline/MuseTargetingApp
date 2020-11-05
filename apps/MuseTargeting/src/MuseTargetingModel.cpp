// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "MuseTargetingModel.h"
#include <QMessageBox>

MuseTargetingModel::MuseTargetingModel(QWidget *parent) : QWidget(parent)
{
    // default observed focus
    m_observedFocus.x() = 0;
    m_observedFocus.y() = 0;
    m_observedFocus.z() = 0;

    // default theoretical focus
    m_theoreticalFocus.x() = 0;
    m_theoreticalFocus.y() = -55;
    m_theoreticalFocus.z() = 0;

    // default calibration
    m_calibration.x() = 0;
    m_calibration.y() = 0;
    m_calibration.z() = 0;

    // default desired focus
    m_desiredFocus.x() = 0;
    m_desiredFocus.y() = 0;
    m_desiredFocus.z() = 0;
}

void MuseTargetingModel::updateCurrentSettings(MuseTargetingSettings* settings){
    
    m_currentSettings.setValue("Psi",settings->getSettingValue("Psi"));
    m_currentSettings.setValue("Theta",settings->getSettingValue("Theta"));
    m_currentSettings.setValue("Alpha", settings->getSettingValue("Alpha"));
    m_currentSettings.setValue("LSlider", settings->getSettingValue("LSlider"));
    m_currentSettings.setValue("XTrolley", settings->getSettingValue("XTrolley"));
    m_currentSettings.setValue("ZTrolley", settings->getSettingValue("ZTrolley"));

    calcTheoreticalFocus();
    
    // if not calibrated and observed focus is set, calibrate
    if (m_isObservedFocusSet && !m_isCalibrated) 
        calibrate();
  
    emit modelChangedSignal();
}

void MuseTargetingModel::updateDesiredFocus(core::Vector3 f) {
    m_desiredFocus.x() = f.x();
    m_desiredFocus.y() = f.y();
    m_desiredFocus.z() = f.z();

    calcSuggestedSettings();

    emit modelChangedSignal();
}

void MuseTargetingModel::updateObservedFocus(core::Vector3 f) {
    m_observedFocus.x() = f.x();
    m_observedFocus.y() = f.y();
    m_observedFocus.z() = f.z();
    m_isObservedFocusSet = true;

    // resetting observed focus automatically resets calibration
    m_calibration.x() = 0;
    m_calibration.y() = 0;
    m_calibration.z() = 0;

    calcTheoreticalFocus();

    // recalibrate
    calibrate();

    emit modelChangedSignal();
}

void MuseTargetingModel::calibrate() {
    if (m_theoreticalFocus.x() != m_observedFocus.x()) {
        if (m_theoreticalFocus.x() > 0) // L, if +LPH
            m_calibration[0] = round(m_observedFocus.x() - abs(m_theoreticalFocus.x()));
        else // R, if +LPH
            m_calibration[0] = round(m_observedFocus.x() + abs(m_theoreticalFocus.x()));
    }
    if (m_theoreticalFocus.y() != m_observedFocus.y()) {
        if (m_theoreticalFocus.y() > 0) // P, if +LPH
            m_calibration[1] = round(m_observedFocus.y() - abs(m_theoreticalFocus.y()));
        else // A, if +LPH
            m_calibration[1] = round(m_observedFocus.y() + abs(m_theoreticalFocus.y()));
    }
    if (m_theoreticalFocus.z() != m_observedFocus.z()) {
        if (m_theoreticalFocus.z() > 0) // H, if +LPH
            m_calibration[2] = round(m_observedFocus.z() - abs(m_theoreticalFocus.z()));
        else // F, if +LPH
            m_calibration[2] = round(m_observedFocus.z() + abs(m_theoreticalFocus.z()));
        m_isCalibrated = true;
    }
}

void MuseTargetingModel::calcTheoreticalFocus(){
    /** Calculates theoretical focus based on m_currentSettings.
    * Populates m_theoreticalFocus.
    * These calculations were translated directly from Muse Targeting v7 (Python).
    * Python code fragments preceed each calculation for reference.
    * */
    //R_psi = np.array(
        //[[1.0, 0.0, 0.0], [0.0, math.cos(math.radians(par.psi)), math.sin(math.radians(par.psi))],
        //[0.0, -math.sin(math.radians(par.psi)), math.cos(math.radians(par.psi))]] )
    double psiRadians = degreesToRadians(m_currentSettings.getSettingValue("Psi"));   // MMK can use Tools.h DegToRad()
    std::vector<std::vector<double>> R_psi{
        {1.0, 0.0, 0.0},
        {0.0, cos(psiRadians), sin(psiRadians)},
        {0.0, -1 * sin(psiRadians), cos(psiRadians)}
    };
    //R_alpha = np.array(
        //[[math.cos(math.radians(par.alpha)), 0.0, -math.sin(math.radians(par.alpha))], [0.0, 1.0, 0.0],
        //[math.sin(math.radians(par.alpha)), 0.0, math.cos(math.radians(par.alpha))]] )
    double alphaRadians = degreesToRadians(m_currentSettings.getSettingValue("Alpha"));
    std::vector<std::vector<double>> R_alpha{
        {cos(alphaRadians), 0.0, -1.0 * sin(alphaRadians)},
        {0.0, 1.0, 0.0},
        {sin(alphaRadians), 0.0, cos(alphaRadians)}
    };
    //R_theta = np.array(
        //[[math.cos(math.radians(par.theta)), 0.0, math.sin(math.radians(par.theta))], [0.0, 1.0, 0.0],
        //[-math.sin(math.radians(par.theta)), 0.0, math.cos(math.radians(par.theta))]] )
    double thetaRadians = degreesToRadians(m_currentSettings.getSettingValue("Theta"));

    std::vector<std::vector<double>> R_theta{
        {cos(thetaRadians), 0.0, sin(thetaRadians)},
        {0.0, 1.0, 0.0},
        {-1.0 * sin(thetaRadians), 0.0, cos(thetaRadians)}
    };
    //R_thetap = np.array(
        //[[math.cos(math.radians(par.theta)), 0.0, -math.sin(math.radians(par.theta))], [0.0, 1.0, 0.0],
        //[math.sin(math.radians(par.theta)), 0.0, math.cos(math.radians(par.theta))]] )
    std::vector<std::vector<double>> R_thetap{
        {cos(thetaRadians), 0.0, -1.0 * sin(thetaRadians)},
        {0.0, 1.0, 0.0},
        {sin(thetaRadians), 0.0, cos(thetaRadians)}
    };
    // xyzf_scanner1 = np.transpose(np.array([[-(par.xoff - par.xtrolley), par.yoff, par.zoff - par.ztrolley]]))
    std::vector<std::vector<double>> xyzf_scanner1{
        {-1.0 * (m_calibration[0] - m_currentSettings.getSettingValue("XTrolley"))},
        {m_calibration[1]},
        {m_calibration[2] - m_currentSettings.getSettingValue("ZTrolley")}
    };
    // xyzf_scanner2A = np.transpose(np.array([[x_cent, y_cent, par.Lslider + z_cent]]))
    std::vector<std::vector<double>> xyzf_scanner2A{
        {m_xcent},
        {m_ycent},
        {m_currentSettings.getSettingValue("LSlider") + m_zcent}
    };
    // xyzin = np.reshape(xyzin, (1, 3))
    std::vector<std::vector<double>> xyzinTranspose{
        { m_xFocus },
        { m_yFocus },
        { m_zFocus }
    };
    // xyzf_scanner2B = np.add(xyzf_scanner2A, (R_psi.dot(R_alpha.dot(np.transpose(xyzin)))))
    std::vector<std::vector<double>> tempDot{
        { (R_alpha[0][0] * xyzinTranspose[0][0]) + (R_alpha[0][1] * xyzinTranspose[1][0]) + (R_alpha[0][2] * xyzinTranspose[2][0]) },
        { (R_alpha[1][0] * xyzinTranspose[0][0]) + (R_alpha[1][1] * xyzinTranspose[1][0]) + (R_alpha[1][2] * xyzinTranspose[2][0]) },
        { (R_alpha[2][0] * xyzinTranspose[0][0]) + (R_alpha[2][1] * xyzinTranspose[1][0]) + (R_alpha[2][2] * xyzinTranspose[2][0])}
    };
    std::vector<std::vector<double>> tempDot2{
        { (R_psi[0][0] * tempDot[0][0]) + (R_psi[0][1] * tempDot[1][0]) + (R_psi[0][2] * tempDot[2][0]) },
        { (R_psi[1][0] * tempDot[0][0]) + (R_psi[1][1] * tempDot[1][0]) + (R_psi[1][2] * tempDot[2][0]) },
        { (R_psi[2][0] * tempDot[0][0]) + (R_psi[2][1] * tempDot[1][0]) + (R_psi[2][2] * tempDot[2][0])}
    };
    std::vector<std::vector<double>> xyzf_scanner2B{
        {xyzf_scanner2A[0][0] + tempDot2[0][0]},
        {xyzf_scanner2A[1][0] + tempDot2[1][0]},
        {xyzf_scanner2A[2][0] + tempDot2[2][0]}
    };
    // xyzf_scanner2C = R_theta.dot(xyzf_scanner2B)
    std::vector<std::vector<double>> xyzf_scanner2C{
        { (R_theta[0][0] * xyzf_scanner2B[0][0]) + (R_theta[0][1] * xyzf_scanner2B[1][0]) + (R_theta[0][2] * xyzf_scanner2B[2][0]) },
        { (R_theta[1][0] * xyzf_scanner2B[0][0]) + (R_theta[1][1] * xyzf_scanner2B[1][0]) + (R_theta[1][2] * xyzf_scanner2B[2][0]) },
        { (R_theta[2][0] * xyzf_scanner2B[0][0]) + (R_theta[2][1] * xyzf_scanner2B[1][0]) + (R_theta[2][2] * xyzf_scanner2B[2][0])}
    };
    // xyzf_scanner2 = xyzf_scanner2C
    // xyzf_scanner = np.add(xyzf_scanner1, xyzf_scanner2)

    std::vector<std::vector<double>> xyzf_scanner{
        {xyzf_scanner1[0][0] + xyzf_scanner2C[0][0]},
        {xyzf_scanner1[1][0] + xyzf_scanner2C[1][0]},
        {xyzf_scanner1[2][0] + xyzf_scanner2C[2][0]}
    };

    //xyzf_transducer = np.add(
    //    (R_theta.dot(np.transpose(np.reshape(np.array([x_cent, y_cent, par.Lslider + z_cent]), (1, 3))))), (
    //        np.transpose(
    //            np.reshape(np.array([-(par.xoff - par.xtrolley), par.yoff, par.zoff - par.ztrolley]),
    //                 (1, 3)))))
    std::vector<std::vector<double>> tempCent{
        {m_xcent},
        {m_ycent},
        {m_currentSettings.getSettingValue("LSlider") + m_zcent}
    };
    std::vector<std::vector<double>> tempDot3{
        { (R_theta[0][0] * tempCent[0][0]) + (R_theta[0][1] * tempCent[1][0]) + (R_theta[0][2] * tempCent[2][0]) },
        { (R_theta[1][0] * tempCent[0][0]) + (R_theta[1][1] * tempCent[1][0]) + (R_theta[1][2] * tempCent[2][0]) },
        { (R_theta[2][0] * tempCent[0][0]) + (R_theta[2][1] * tempCent[1][0]) + (R_theta[2][2] * tempCent[2][0]) }
    };
    std::vector<std::vector<double>> tempCalib{
        { -1.0 * (m_calibration[0] - m_currentSettings.getSettingValue("XTrolley")) },
        { m_calibration[1] },
        { m_calibration[2] - m_currentSettings.getSettingValue("ZTrolley") }
    };
    std::vector<std::vector<double>> xyzf_transducer{
        {tempDot3[0][0] + tempCalib[0][0]},
        {tempDot3[1][0] + tempCalib[1][0]},
        {tempDot3[2][0] + tempCalib[2][0]}
    };
    // create calculated focus string by defining xyzf_scanner in terms of LPH+
    // par.xyzRAH = 'RPH'           # Right, Posterior, Head
    // par.xyzRAHneg = 'LAF'        # Left, Anterior, Foot
    // xyzf = np.absolute(xyzf_scanner)
    // if xyzf_scanner[0] < 0:
    //     xyzRAH[0] = par.xyzRAHneg[0]
    // if xyzf_scanner[1] < 0 :
    //     xyzRAH[1] = par.xyzRAHneg[1]
    // if xyzf_scanner[2] < 0 :
    //     xyzRAH[2] = par.xyzRAHneg[2]
    std::vector<std::vector<double>> xyzf{
        { abs(xyzf_scanner[0][0]) },
        { abs(xyzf_scanner[1][0]) },
        { abs(xyzf_scanner[2][0]) }
    };

    // MMK question: in Python MuseTargeting,
    // xyzRAH = ['R', 'P', 'H']  # Changed L to R
    // xyzRAHneg = ['L', 'A', 'F']  # Changed R to L
    m_theoreticalFocus.x() = -1 * round(xyzf_scanner[0][0]); // why?
    m_theoreticalFocus.y() = round(xyzf_scanner[1][0]);
    m_theoreticalFocus.z() = round(xyzf_scanner[2][0]);
}

void MuseTargetingModel::calcSuggestedSettings() {
    
    // dydz = (par.yfMRIwant - par.yoff - par.ycent)/ par.zfocus
    // par.calc_psi = math.degrees(math.asin((par.yfMRIwant - par.yoff - par.ycent)/ par.zfocus))
    double suggestedPsi = radiansToDegrees(asin((m_desiredFocus.y() - m_calibration[1] - m_ycent) / m_zFocus));
    // R_calc_psi = np.array(
    //    [[1.0, 0.0, 0.0], [0.0, math.cos(math.radians(par.calc_psi)), math.sin(math.radians(par.calc_psi))],
    //    [0.0, -math.sin(math.radians(par.calc_psi)), math.cos(math.radians(par.calc_psi))]] )
    double suggestedPsiRadians = degreesToRadians(suggestedPsi);
    std::vector<std::vector<double>> R_calc_psi{
        { 1.0, 0.0, 0.0 },
        { 0.0, cos(suggestedPsiRadians), sin(suggestedPsiRadians)},
        { 0.0, -1.0 * sin(suggestedPsiRadians), cos(suggestedPsiRadians)}
    };
    // if int(par.usetheta) == 1: par.calc_theta = par.theta
    //    if int(par.usealpha) == 1 : par.calc_alpha = par.alpha
    //        if int(par.useLslider) == 1 : par.calc_Lslider = par.Lslider
    // # we can't calculate theta yet - so we have to use the original anyway.
    double suggestedTheta = m_currentSettings.getSettingValue("Theta");
    double suggestedAlpha = m_currentSettings.getSettingValue("Alpha");
    double suggestedLSlider = m_currentSettings.getSettingValue("LSlider");
    // xyzfMRIpsi1 = np.transpose(np.array([[-(par.xoff - par.calc_xtrolley), par.yoff, par.zoff - par.calc_ztrolley]]))
    std::vector<std::vector<double>> xyzfMRIpsi1;
    /*if (m_isPersistSet) {
        xyzfMRIpsi1 = {
            { -1.0 * m_calibration[0] - m_persistX },
            { m_calibration[1] },
            { m_calibration[2] - m_persistZ }
        };
    }*/
    //else {
        xyzfMRIpsi1 = {
            { -1.0 * (m_calibration[0] - m_suggestedSettings.getSettingValue("XTrolley")) },
            { m_calibration[1] },
            { m_calibration[2] - m_suggestedSettings.getSettingValue("ZTrolley") }
        };
    //}
    // xyzfMRIpsi2A = np.transpose(np.array([[x_cent, y_cent, par.calc_Lslider + z_cent]]))
    std::vector<std::vector<double>> xyzfMRIpsi2A{
        { m_xcent },
        { m_ycent },
        { m_suggestedSettings.getSettingValue("LSlider") + m_zcent }
    };
    // debugging
    //    double temp = m_suggestedSettings.getSettingValue("LSlider");
    //    qDebug() << "m_suggestedSettings.getSettingValue LSlider" << temp;
    //    qDebug() << "xyzfMRIpis2A " << xyzfMRIpsi2A[0] << " " << xyzfMRIpsi2A[1] << " " << xyzfMRIpsi2A[2];
        //
        // xyzfMRIpsi2B = np.add(xyzfMRIpsi2A, (R_calc_psi.dot(R_alpha.dot(np.transpose(xyzin)))))
    double alphaRadians = degreesToRadians(m_currentSettings.getSettingValue("Alpha"));
    std::vector<std::vector<double>> R_alpha{
        {cos(alphaRadians), 0.0, -1.0 * sin(alphaRadians)},
        {0.0, 1.0, 0.0},
        {sin(alphaRadians), 0.0, cos(alphaRadians)}
    };
    std::vector<std::vector<double>> xyzinTranspose{  // MMK reuse from getTheoreticalFocus()?
        { m_xFocus },
        { m_yFocus },
        { m_zFocus }
    };
    std::vector<std::vector<double>> tempDot{  // MMK reuse from getTheoreticalFocus()?
        { (R_alpha[0][0] * xyzinTranspose[0][0]) + (R_alpha[0][1] * xyzinTranspose[1][0]) + (R_alpha[0][2] * xyzinTranspose[2][0]) },
        { (R_alpha[1][0] * xyzinTranspose[0][0]) + (R_alpha[1][1] * xyzinTranspose[1][0]) + (R_alpha[1][2] * xyzinTranspose[2][0]) },
        { (R_alpha[2][0] * xyzinTranspose[0][0]) + (R_alpha[2][1] * xyzinTranspose[1][0]) + (R_alpha[2][2] * xyzinTranspose[2][0])}
    };
    std::vector<std::vector<double>> tempDot2{
        { (R_calc_psi[0][0] * tempDot[0][0]) + (R_calc_psi[0][1] * tempDot[1][0]) + (R_calc_psi[0][2] * tempDot[2][0]) },
        { (R_calc_psi[1][0] * tempDot[0][0]) + (R_calc_psi[1][1] * tempDot[1][0]) + (R_calc_psi[1][2] * tempDot[2][0]) },
        { (R_calc_psi[2][0] * tempDot[0][0]) + (R_calc_psi[2][1] * tempDot[1][0]) + (R_calc_psi[2][2] * tempDot[2][0])}
    };
    std::vector<std::vector<double>> xyzfMRIpsi2B{
        {xyzfMRIpsi2A[0][0] + tempDot2[0][0]},
        {xyzfMRIpsi2A[1][0] + tempDot2[1][0]},
        {xyzfMRIpsi2A[2][0] + tempDot2[2][0]}
    };
    // xyzfMRIpsi2C = R_theta.dot(xyzfMRIpsi2B)
    double thetaRadians = degreesToRadians(m_currentSettings.getSettingValue("Theta"));
    std::vector<std::vector<double>> R_theta{  // MMK reuse from getTheoreticalFocus()?
        {cos(thetaRadians), 0.0, sin(thetaRadians)},
        {0.0, 1.0, 0.0},
        {-1.0 * sin(thetaRadians), 0.0, cos(thetaRadians)}
    };
    std::vector<std::vector<double>> xyzfMRIpsi2C{  // MMK reuse from getTheoreticalFocus()?
        { (R_theta[0][0] * xyzfMRIpsi2B[0][0]) + (R_theta[0][1] * xyzfMRIpsi2B[1][0]) + (R_theta[0][2] * xyzfMRIpsi2B[2][0]) },
        { (R_theta[1][0] * xyzfMRIpsi2B[0][0]) + (R_theta[1][1] * xyzfMRIpsi2B[1][0]) + (R_theta[1][2] * xyzfMRIpsi2B[2][0]) },
        { (R_theta[2][0] * xyzfMRIpsi2B[0][0]) + (R_theta[2][1] * xyzfMRIpsi2B[1][0]) + (R_theta[2][2] * xyzfMRIpsi2B[2][0])}
    };
    // xyzfMRIpsi = np.add(xyzfMRIpsi1, xyzfMRIpsi2C)
    std::vector<double> xyzfMRIpsi{
        xyzfMRIpsi1[0][0] + xyzfMRIpsi2C[0][0],
        xyzfMRIpsi1[1][0] + xyzfMRIpsi2C[1][0],
        xyzfMRIpsi1[2][0] + xyzfMRIpsi2C[2][0]
    };
    // dxyz = np.add(par.xyzfMRIwant, -xyzfMRIpsi)
    std::vector<double> dxyz{
        (-1 * m_desiredFocus.x()) + -1.0 * xyzfMRIpsi[0],  // MuseTargeting Python negates user-entered desired focus x
        m_desiredFocus.y() + -1.0 * xyzfMRIpsi[1],
        m_desiredFocus.z() + -1.0 * xyzfMRIpsi[2]
    };
    // abs_dxyz = math.sqrt(dxyz.dot(np.transpose(dxyz)))
    std::vector<std::vector<double>> dxyzTranspose{
        {dxyz[0]},
        {dxyz[1]},
        {dxyz[2]}
    };
    double tempDot3 = (dxyz[0] * dxyzTranspose[0][0]) + (dxyz[1] * dxyzTranspose[1][0]) + (dxyz[2] * dxyzTranspose[2][0]);
    double abs_dxyz = sqrt(tempDot3);
    //  if abs_dxyz > 0.5:
    //    par.calc_psi = par.calc_psi + 180 * (dxyz[0, 1] / xyzin[0, 2]) / 3.1415926  # math.pi instead of 3.1415926 05 / 25 / 18 DP
    //    R_calc_psi = np.array(
    //        [[1.0, 0.0, 0.0],
    //        [0.0, math.cos(math.radians(par.calc_psi)), math.sin(math.radians(par.calc_psi))],
    //        [0.0, -math.sin(math.radians(par.calc_psi)), math.cos(math.radians(par.calc_psi))]] )
    if (abs_dxyz > 0.5)
    {
        suggestedPsi = suggestedPsi + 180 * (dxyz[1] / m_zFocus) / M_PI;
        R_calc_psi[0][0] = 1.0;
        R_calc_psi[0][1] = 0.0;
        R_calc_psi[0][2] = 0.0;
        R_calc_psi[1][0] = 0.0;
        R_calc_psi[1][1] = cos(degreesToRadians(suggestedPsi));
        R_calc_psi[1][2] = sin(degreesToRadians(suggestedPsi));
        R_calc_psi[2][0] = 0.0;
        R_calc_psi[2][1] = -1 * sin(degreesToRadians(suggestedPsi));
        R_calc_psi[2][2] = cos(degreesToRadians(suggestedPsi));
    }
    // xtest = par.calc_xtrolley + dxyz[0, 0]  #  % calc_xtrolley is added
    // ztest = par.calc_ztrolley - dxyz[0, 2]  #  % calc_ztrolley is subtracted
    // par.calc_xtrolley = xtest
    // par.calc_ztrolley = ztest
    double xtest;
    double ztest;
    //if (!m_isPersistSet) {
        xtest = m_suggestedSettings.getSettingValue("XTrolley") + dxyz[0];
        ztest = m_suggestedSettings.getSettingValue("ZTrolley") - dxyz[2];
    //}
    //else {
        //xtest = m_persistX + dxyz[0];
        //ztest = m_persistZ - dxyz[2];
    //}
    double suggestedXTrolley = xtest;
    double suggestedZTrolley = ztest;
    /*if (!m_isPersistSet) {
        m_persistX = xtest;
        m_persistZ = ztest;
        m_isPersistSet = true;
    }*/

    m_suggestedSettings.setValue("Psi", suggestedPsi);
    m_suggestedSettings.setValue("Theta", suggestedTheta);
    m_suggestedSettings.setValue("Alpha", suggestedAlpha);
    m_suggestedSettings.setValue("LSlider", suggestedLSlider);
    m_suggestedSettings.setValue("XTrolley", suggestedXTrolley);
    m_suggestedSettings.setValue("ZTrolley", suggestedZTrolley);
}

void MuseTargetingModel::reset() {
    m_currentSettings.resetToDefault();
    m_suggestedSettings.resetToDefault();
    m_theoreticalFocus.x() = 0;
    m_theoreticalFocus.y() = -55;
    m_theoreticalFocus.z() = 0;
    m_calibration.x() = 0;
    m_calibration.y() = 0;
    m_calibration.z() = 0;
    m_isCalibrated = false;
    m_desiredFocus.x() = 0;
    m_desiredFocus.y() = 0;
    m_desiredFocus.z() = 0;

    emit modelChangedSignal();
}