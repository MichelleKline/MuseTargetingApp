// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "MuseTargetingView.h"
#include "MuseTargetingSettings.h"
#include <QDebug>
#include <QMessageBox>

MuseTargetingView::MuseTargetingView(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    refreshView();

    connect(ui.currentSettingButton, SIGNAL(clicked()), this, SLOT(enterButtonClicked()));
    connect(this, SIGNAL(updateCurrentSettings(MuseTargetingSettings*)), &m_model, SLOT(updateCurrentSettings(MuseTargetingSettings*)));
    connect(&m_model, SIGNAL(modelChangedSignal()), this, SLOT(refreshView()));
    connect(ui.calculateButton, SIGNAL(clicked()), this, SLOT(calculateButtonClicked()));
    connect(this, SIGNAL(updateDesiredFocus(core::Vector3)), &m_model, SLOT(updateDesiredFocus(core::Vector3)));
    connect(ui.resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
}

MuseTargetingView::~MuseTargetingView()
{}

void MuseTargetingView::enterButtonClicked() 
{
    // get the current system settings that the user has entered, validate,
    // and update the model
    MuseTargetingSettings* s = new MuseTargetingSettings;
    // Psi
    QString currentPsiStr = ui.currentPsiLineEdit->text();
    double currentPsi = currentPsiStr.toDouble();
    if (currentPsi < m_model.getCurrentSettingMin("Psi") || currentPsi > m_model.getCurrentSettingMax("Psi"))
    {
        invalidMessage("Psi");
        return;
    }
    s->setValue("Psi", currentPsi);
    // Theta
    QString currentThetaStr = ui.currentThetaLineEdit->text();
    double currentTheta = currentThetaStr.toDouble();
    if (currentTheta < m_model.getCurrentSettingMin("Theta") || currentTheta > m_model.getCurrentSettingMax("Theta"))
    {
        invalidMessage("Theta");
        return;
    }
    s->setValue("Theta", currentTheta);
    // Alpha
    QString currentAlphaStr = ui.currentAlphaLineEdit->text();
    double currentAlpha = currentAlphaStr.toDouble();
    if (currentAlpha < m_model.getCurrentSettingMin("Alpha") || currentAlpha > m_model.getCurrentSettingMax("Alpha"))
    {
        invalidMessage("Alpha");
        return;
    }
    s->setValue("Alpha", currentAlpha);
    // L-Slider
    QString currentLSliderStr = ui.currentLSliderLineEdit->text();
    double currentLSlider = currentLSliderStr.toDouble();
    if (currentLSlider < m_model.getCurrentSettingMin("LSlider") || currentLSlider > m_model.getCurrentSettingMax("LSlider"))
    {
        invalidMessage("LSlider");
        return;
    }
    s->setValue("LSlider", currentLSlider);
    // X-Trolley
    QString currentXTrolleyStr = ui.currentXTrolleyLineEdit->text();
    double currentXTrolley = currentXTrolleyStr.toDouble();
    if (currentXTrolley < m_model.getCurrentSettingMin("XTrolley") || currentXTrolley > m_model.getCurrentSettingMax("XTrolley"))
    {
        invalidMessage("XTrolley");
        return;
    }
    s->setValue("XTrolley", currentXTrolley);
    // Z-Trolley
    QString currentZTrolleyStr = ui.currentZTrolleyLineEdit->text();
    double currentZTrolley = currentZTrolleyStr.toDouble();
    if (currentZTrolley < m_model.getCurrentSettingMin("ZTrolley") || currentZTrolley > m_model.getCurrentSettingMax("ZTrolley"))
    {
        invalidMessage("ZTrolley");
        return;
    }
    s->setValue("ZTrolley", currentZTrolley);
    
    emit updateCurrentSettings(s);
    delete s; 
}

void MuseTargetingView::calculateButtonClicked() {
    // get desired focus from ui
    QString desiredXString = ui.desiredXEdit->toPlainText();
    QString desiredYString = ui.desiredYEdit->toPlainText();
    QString desiredZString = ui.desiredZEdit->toPlainText();
    core::Vector3 df;
    df.x() = desiredXString.toDouble();
    df.y() = desiredYString.toDouble();
    df.z() = desiredZString.toDouble();

    emit updateDesiredFocus(df);
    //emit calculateSuggestedSettings();
}

void MuseTargetingView::resetButtonClicked() {
    m_model.reset();
}

void MuseTargetingView::invalidMessage(QString settingName) {
    QString msg = settingName + " setting limits: " + QString::number(m_model.getCurrentSettingMin(settingName)) +
        " - " + QString::number(m_model.getCurrentSettingMax(settingName));
    QMessageBox::warning(this, "Invalid Entry", msg);
}

void MuseTargetingView::refreshView() {
    // display observed focus widgets
    core::Vector3 of = m_model.getObservedFocus();
    ui.observedXEdit->setText(QString::number(of.x()));
    ui.observedYEdit->setText(QString::number(of.y()));
    ui.observedZEdit->setText(QString::number(of.z()));

    // display current settings 
    MuseTargetingSettings* cs = m_model.getCurrentSettings();
    ui.currentPsiLineEdit->setText(QString::number(round(cs->getSettingValue("Psi"))));
    ui.currentThetaLineEdit->setText(QString::number(round(cs->getSettingValue("Theta"))));
    ui.currentAlphaLineEdit->setText(QString::number(round(cs->getSettingValue("Alpha"))));
    ui.currentLSliderLineEdit->setText(QString::number(round(cs->getSettingValue("LSlider"))));
    ui.currentXTrolleyLineEdit->setText(QString::number(round(cs->getSettingValue("XTrolley"))));
    ui.currentZTrolleyLineEdit->setText(QString::number(round(cs->getSettingValue("ZTrolley"))));
    
    // display calibration <=== TEMP, during dev
    core::Vector3 cf = m_model.getCalibration();
    ui.calibrationXEdit->setText(QString::number(cf.x()));
    ui.calibrationYEdit->setText(QString::number(cf.y()));
    ui.calibrationZEdit->setText(QString::number(cf.z()));

    // display theoretical focus <=== TEMP, during dev
    core::Vector3 tf = m_model.getTheoreticalFocus();
    ui.theoreticalXEdit->setText(QString::number(tf.x()));
    ui.theoreticalYEdit->setText(QString::number(tf.y()));
    ui.theoreticalZEdit->setText(QString::number(tf.z()));

    // display desired focus
    core::Vector3 df = m_model.getDesiredFocus();
    ui.desiredXEdit->setText(QString::number(df.x()));
    ui.desiredYEdit->setText(QString::number(df.y()));
    ui.desiredZEdit->setText(QString::number(df.z()));

    // update suggested settings widgets
    MuseTargetingSettings* ss = m_model.getSuggestedSettings();
    ui.suggestedPsiLineEdit->setText(QString::number(round(ss->getSettingValue("Psi"))));
    ui.suggestedThetaLineEdit->setText(QString::number(round(ss->getSettingValue("Theta"))));
    ui.suggestedAlphaLineEdit->setText(QString::number(round(ss->getSettingValue("Alpha"))));
    ui.suggestedLSliderLineEdit->setText(QString::number(round(ss->getSettingValue("LSlider"))));
    ui.suggestedXTrolleyLineEdit->setText(QString::number(round(ss->getSettingValue("XTrolley"))));
    ui.suggestedZTrolleyLineEdit->setText(QString::number(round(ss->getSettingValue("ZTrolley"))));
}
