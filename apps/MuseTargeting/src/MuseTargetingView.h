#ifndef MUSETARGETINGVIEW_H
#define MUSETARGETINGVIEW_H

#include <QtWidgets/QWidget>
#include "ui_MuseTargetingView.h"
#include "MuseTargetingModel.h"
#include "MuseTargetingSettings.h"
#include "../../libs/libCore/Core/Maths/Vector3.h"

class MuseTargetingView : public QWidget
{
    Q_OBJECT

public:
    MuseTargetingView(QWidget* parent = nullptr);
    ~MuseTargetingView();

private slots:
    void enterButtonClicked();
    void refreshView();
    void calculateButtonClicked();

signals:
    void updateCurrentSettings(MuseTargetingSettings* s);
    void calculateFocus();
    void updateDesiredFocus(core::Vector3 df);
    void calculateSuggestedSettings();

private:
    Ui::MuseTargetingViewClass ui;
    MuseTargetingModel m_model;
};
#endif // MUSETARGETINGVIEW_H
