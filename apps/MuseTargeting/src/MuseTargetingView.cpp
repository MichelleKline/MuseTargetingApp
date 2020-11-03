
#include "MuseTargetingView.h"
#include "MuseTargetingSettings.h"
#include <QDebug>

MuseTargetingView::MuseTargetingView(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    refreshView();

    connect(ui.currentSettingButton, SIGNAL(clicked()), this, SLOT(enterButtonClicked()));
    connect(this, SIGNAL(updateCurrentSettings(MuseTargetingSettings*)), &m_model, SLOT(updateCurrentSettings(MuseTargetingSettings*)));
    connect(this, SIGNAL(calculateFocus()), &m_model, SLOT(calcTheoreticalFocus()));
    connect(&m_model, SIGNAL(modelChangedSignal()), this, SLOT(refreshView()));
    connect(ui.calculateButton, SIGNAL(clicked()), this, SLOT(calculateButtonClicked()));
    connect(this, SIGNAL(updateDesiredFocus(core::Vector3)), &m_model, SLOT(updateDesiredFocus(core::Vector3)));
    connect(this, SIGNAL(calculateSuggestedSettings()), &m_model, SLOT(calcSuggestedSettings()));
}

MuseTargetingView::~MuseTargetingView()
{
    
}

void MuseTargetingView::enterButtonClicked() 
{
    // get the current system settings that the user has entered
    // and update the model
    MuseTargetingSettings* s = new MuseTargetingSettings;
    QString currentPsiStr = ui.currentPsiLineEdit->text();
    s->setValue("Psi", currentPsiStr.toDouble());
    QString currentThetaStr = ui.currentThetaLineEdit->text();
    s->setValue("Theta", currentThetaStr.toDouble());
    QString currentAlphaStr = ui.currentAlphaLineEdit->text();
    s->setValue("Alpha", currentAlphaStr.toDouble());
    QString currentLSliderStr = ui.currentLSliderLineEdit->text();
    s->setValue("LSlider", currentLSliderStr.toDouble());
    QString currentXTrolleyStr = ui.currentXTrolleyLineEdit->text();
    s->setValue("XTrolley", currentXTrolleyStr.toDouble());
    QString currentZTrolleyStr = ui.currentZTrolleyLineEdit->text();
    s->setValue("ZTrolley", currentZTrolleyStr.toDouble());
    // MMK fixme: ask Stéphanie
    // delete s?

    core::Vector3 v;
    emit updateCurrentSettings(s);
    emit calculateFocus();
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
    emit calculateSuggestedSettings();
}

void MuseTargetingView::refreshView() {
    // update observed focus widgets
    core::Vector3 of = m_model.getObservedFocus();
    ui.observedXEdit->setText(QString::number(of.x()));
    ui.observedYEdit->setText(QString::number(of.y()));
    ui.observedZEdit->setText(QString::number(of.z()));

    // update current settings 
    MuseTargetingSettings* cs = m_model.getCurrentSettings();
    ui.currentPsiLineEdit->setText(QString::number(cs->getSettingValue("Psi")));
    ui.currentThetaLineEdit->setText(QString::number(cs->getSettingValue("Theta")));
    ui.currentAlphaLineEdit->setText(QString::number(cs->getSettingValue("Alpha")));
    ui.currentLSliderLineEdit->setText(QString::number(cs->getSettingValue("LSlider")));
    ui.currentXTrolleyLineEdit->setText(QString::number(cs->getSettingValue("XTrolley")));
    ui.currentZTrolleyLineEdit->setText(QString::number(cs->getSettingValue("ZTrolley")));
    
    // update calibration widgets <=== TEMP, during dev
    core::Vector3 cf = m_model.getCalibration();
    ui.calibrationXEdit->setText(QString::number(cf.x()));
    ui.calibrationYEdit->setText(QString::number(cf.y()));
    ui.calibrationZEdit->setText(QString::number(cf.z()));

    // update theoretical focus widgets <=== TEMP, during dev
    core::Vector3 tf = m_model.getTheoreticalFocus();
    ui.theoreticalXEdit->setText(QString::number(tf.x()));
    ui.theoreticalYEdit->setText(QString::number(tf.y()));
    ui.theoreticalZEdit->setText(QString::number(tf.z()));

    // update desired focus
    core::Vector3 df = m_model.getDesiredFocus();
    ui.desiredXEdit->setText(QString::number(df.x()));
    ui.desiredYEdit->setText(QString::number(df.y()));
    ui.desiredZEdit->setText(QString::number(df.z()));

    // update suggested settings widgets
    MuseTargetingSettings* ss = m_model.getSuggestedSettings();
    ui.suggestedPsiLineEdit->setText(QString::number(ss->getSettingValue("Psi")));
    ui.suggestedThetaLineEdit->setText(QString::number(ss->getSettingValue("Theta")));
    ui.suggestedAlphaLineEdit->setText(QString::number(ss->getSettingValue("Alpha")));
    ui.suggestedLSliderLineEdit->setText(QString::number(ss->getSettingValue("LSlider")));
    ui.suggestedXTrolleyLineEdit->setText(QString::number(ss->getSettingValue("XTrolley")));
    ui.suggestedZTrolleyLineEdit->setText(QString::number(ss->getSettingValue("ZTrolley")));
}
