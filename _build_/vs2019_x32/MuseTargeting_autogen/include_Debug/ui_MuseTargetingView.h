/********************************************************************************
** Form generated from reading UI file 'MuseTargetingView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSETARGETINGVIEW_H
#define UI_MUSETARGETINGVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MuseTargetingViewClass
{
public:
    QGroupBox *currentSettingsGroup;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *currentPsiLabel;
    QLineEdit *currentPsiLineEdit;
    QLabel *currentThetaLabel;
    QLineEdit *currentThetaLineEdit;
    QLabel *currentAlphaLabel;
    QLineEdit *currentAlphaLineEdit;
    QLabel *currentLSliderLabel;
    QLineEdit *currentLSliderLineEdit;
    QLabel *currentXTrolleyLabel;
    QLineEdit *currentXTrolleyLineEdit;
    QLabel *currentZTrolleyLabel;
    QLineEdit *currentZTrolleyLineEdit;
    QPushButton *currentSettingButton;
    QGroupBox *suggestedSettingsGroup;
    QSplitter *splitter_2;
    QWidget *layoutWidget1;
    QFormLayout *formLayout_2;
    QLabel *suggestedPsiLabel;
    QLineEdit *suggestedPsiLineEdit;
    QLabel *suggestedThetaLabel;
    QLineEdit *suggestedThetaLineEdit;
    QLabel *suggestedAlphaLabel;
    QLineEdit *suggestedAlphaLineEdit;
    QLabel *suggestedLSliderLabel;
    QLineEdit *suggestedLSliderLineEdit;
    QLabel *suggestedXTrolleyLabel;
    QLineEdit *suggestedXTrolleyLineEdit;
    QLabel *suggestedZTrolleyLabel;
    QLineEdit *suggestedZTrolleyLineEdit;
    QPushButton *calculateButton;
    QGroupBox *observedFocusGroup;
    QGroupBox *observedFocusGroup_3;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_3;
    QTextEdit *observedXEdit_2;
    QTextEdit *observedZEdit_2;
    QTextEdit *observedYEdit_2;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QTextEdit *observedXEdit;
    QTextEdit *observedZEdit;
    QTextEdit *observedYEdit;
    QGroupBox *desiredFocusGroup;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_2;
    QTextEdit *desiredXEdit;
    QTextEdit *desiredZEdit;
    QTextEdit *desiredYEdit;
    QGroupBox *calibrationGroup;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_4;
    QTextEdit *calibrationXEdit;
    QTextEdit *calibrationZEdit;
    QTextEdit *calibrationYEdit;
    QGroupBox *theoreticalFocusGroup;
    QWidget *layoutWidget_4;
    QGridLayout *gridLayout_5;
    QTextEdit *theoreticalXEdit;
    QTextEdit *theoreticalZEdit;
    QTextEdit *theoreticalYEdit;
    QPushButton *resetButton;

    void setupUi(QWidget *MuseTargetingViewClass)
    {
        if (MuseTargetingViewClass->objectName().isEmpty())
            MuseTargetingViewClass->setObjectName(QString::fromUtf8("MuseTargetingViewClass"));
        MuseTargetingViewClass->resize(511, 524);
        currentSettingsGroup = new QGroupBox(MuseTargetingViewClass);
        currentSettingsGroup->setObjectName(QString::fromUtf8("currentSettingsGroup"));
        currentSettingsGroup->setGeometry(QRect(20, 110, 221, 201));
        currentSettingsGroup->setAlignment(Qt::AlignCenter);
        splitter = new QSplitter(currentSettingsGroup);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(20, 20, 183, 175));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        currentPsiLabel = new QLabel(layoutWidget);
        currentPsiLabel->setObjectName(QString::fromUtf8("currentPsiLabel"));
        currentPsiLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, currentPsiLabel);

        currentPsiLineEdit = new QLineEdit(layoutWidget);
        currentPsiLineEdit->setObjectName(QString::fromUtf8("currentPsiLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, currentPsiLineEdit);

        currentThetaLabel = new QLabel(layoutWidget);
        currentThetaLabel->setObjectName(QString::fromUtf8("currentThetaLabel"));
        currentThetaLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, currentThetaLabel);

        currentThetaLineEdit = new QLineEdit(layoutWidget);
        currentThetaLineEdit->setObjectName(QString::fromUtf8("currentThetaLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, currentThetaLineEdit);

        currentAlphaLabel = new QLabel(layoutWidget);
        currentAlphaLabel->setObjectName(QString::fromUtf8("currentAlphaLabel"));
        currentAlphaLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, currentAlphaLabel);

        currentAlphaLineEdit = new QLineEdit(layoutWidget);
        currentAlphaLineEdit->setObjectName(QString::fromUtf8("currentAlphaLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, currentAlphaLineEdit);

        currentLSliderLabel = new QLabel(layoutWidget);
        currentLSliderLabel->setObjectName(QString::fromUtf8("currentLSliderLabel"));
        currentLSliderLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, currentLSliderLabel);

        currentLSliderLineEdit = new QLineEdit(layoutWidget);
        currentLSliderLineEdit->setObjectName(QString::fromUtf8("currentLSliderLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, currentLSliderLineEdit);

        currentXTrolleyLabel = new QLabel(layoutWidget);
        currentXTrolleyLabel->setObjectName(QString::fromUtf8("currentXTrolleyLabel"));
        currentXTrolleyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(4, QFormLayout::LabelRole, currentXTrolleyLabel);

        currentXTrolleyLineEdit = new QLineEdit(layoutWidget);
        currentXTrolleyLineEdit->setObjectName(QString::fromUtf8("currentXTrolleyLineEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, currentXTrolleyLineEdit);

        currentZTrolleyLabel = new QLabel(layoutWidget);
        currentZTrolleyLabel->setObjectName(QString::fromUtf8("currentZTrolleyLabel"));
        currentZTrolleyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(5, QFormLayout::LabelRole, currentZTrolleyLabel);

        currentZTrolleyLineEdit = new QLineEdit(layoutWidget);
        currentZTrolleyLineEdit->setObjectName(QString::fromUtf8("currentZTrolleyLineEdit"));

        formLayout->setWidget(5, QFormLayout::FieldRole, currentZTrolleyLineEdit);

        splitter->addWidget(layoutWidget);
        currentSettingButton = new QPushButton(splitter);
        currentSettingButton->setObjectName(QString::fromUtf8("currentSettingButton"));
        splitter->addWidget(currentSettingButton);
        suggestedSettingsGroup = new QGroupBox(MuseTargetingViewClass);
        suggestedSettingsGroup->setObjectName(QString::fromUtf8("suggestedSettingsGroup"));
        suggestedSettingsGroup->setGeometry(QRect(270, 110, 221, 201));
        suggestedSettingsGroup->setAlignment(Qt::AlignCenter);
        splitter_2 = new QSplitter(suggestedSettingsGroup);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(20, 20, 183, 175));
        splitter_2->setOrientation(Qt::Vertical);
        layoutWidget1 = new QWidget(splitter_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        formLayout_2 = new QFormLayout(layoutWidget1);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        suggestedPsiLabel = new QLabel(layoutWidget1);
        suggestedPsiLabel->setObjectName(QString::fromUtf8("suggestedPsiLabel"));
        suggestedPsiLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, suggestedPsiLabel);

        suggestedPsiLineEdit = new QLineEdit(layoutWidget1);
        suggestedPsiLineEdit->setObjectName(QString::fromUtf8("suggestedPsiLineEdit"));
        suggestedPsiLineEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        suggestedPsiLineEdit->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, suggestedPsiLineEdit);

        suggestedThetaLabel = new QLabel(layoutWidget1);
        suggestedThetaLabel->setObjectName(QString::fromUtf8("suggestedThetaLabel"));
        suggestedThetaLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, suggestedThetaLabel);

        suggestedThetaLineEdit = new QLineEdit(layoutWidget1);
        suggestedThetaLineEdit->setObjectName(QString::fromUtf8("suggestedThetaLineEdit"));
        suggestedThetaLineEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        suggestedThetaLineEdit->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, suggestedThetaLineEdit);

        suggestedAlphaLabel = new QLabel(layoutWidget1);
        suggestedAlphaLabel->setObjectName(QString::fromUtf8("suggestedAlphaLabel"));
        suggestedAlphaLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, suggestedAlphaLabel);

        suggestedAlphaLineEdit = new QLineEdit(layoutWidget1);
        suggestedAlphaLineEdit->setObjectName(QString::fromUtf8("suggestedAlphaLineEdit"));
        suggestedAlphaLineEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        suggestedAlphaLineEdit->setReadOnly(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, suggestedAlphaLineEdit);

        suggestedLSliderLabel = new QLabel(layoutWidget1);
        suggestedLSliderLabel->setObjectName(QString::fromUtf8("suggestedLSliderLabel"));
        suggestedLSliderLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, suggestedLSliderLabel);

        suggestedLSliderLineEdit = new QLineEdit(layoutWidget1);
        suggestedLSliderLineEdit->setObjectName(QString::fromUtf8("suggestedLSliderLineEdit"));
        suggestedLSliderLineEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        suggestedLSliderLineEdit->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, suggestedLSliderLineEdit);

        suggestedXTrolleyLabel = new QLabel(layoutWidget1);
        suggestedXTrolleyLabel->setObjectName(QString::fromUtf8("suggestedXTrolleyLabel"));
        suggestedXTrolleyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, suggestedXTrolleyLabel);

        suggestedXTrolleyLineEdit = new QLineEdit(layoutWidget1);
        suggestedXTrolleyLineEdit->setObjectName(QString::fromUtf8("suggestedXTrolleyLineEdit"));
        suggestedXTrolleyLineEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        suggestedXTrolleyLineEdit->setReadOnly(true);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, suggestedXTrolleyLineEdit);

        suggestedZTrolleyLabel = new QLabel(layoutWidget1);
        suggestedZTrolleyLabel->setObjectName(QString::fromUtf8("suggestedZTrolleyLabel"));
        suggestedZTrolleyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(5, QFormLayout::LabelRole, suggestedZTrolleyLabel);

        suggestedZTrolleyLineEdit = new QLineEdit(layoutWidget1);
        suggestedZTrolleyLineEdit->setObjectName(QString::fromUtf8("suggestedZTrolleyLineEdit"));
        suggestedZTrolleyLineEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        suggestedZTrolleyLineEdit->setReadOnly(true);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, suggestedZTrolleyLineEdit);

        splitter_2->addWidget(layoutWidget1);
        calculateButton = new QPushButton(splitter_2);
        calculateButton->setObjectName(QString::fromUtf8("calculateButton"));
        splitter_2->addWidget(calculateButton);
        observedFocusGroup = new QGroupBox(MuseTargetingViewClass);
        observedFocusGroup->setObjectName(QString::fromUtf8("observedFocusGroup"));
        observedFocusGroup->setGeometry(QRect(60, 20, 161, 81));
        observedFocusGroup->setMaximumSize(QSize(16777210, 16777215));
        observedFocusGroup->setAlignment(Qt::AlignCenter);
        observedFocusGroup_3 = new QGroupBox(observedFocusGroup);
        observedFocusGroup_3->setObjectName(QString::fromUtf8("observedFocusGroup_3"));
        observedFocusGroup_3->setGeometry(QRect(0, 0, 161, 81));
        observedFocusGroup_3->setMaximumSize(QSize(16777210, 16777215));
        observedFocusGroup_3->setAlignment(Qt::AlignCenter);
        layoutWidget_2 = new QWidget(observedFocusGroup_3);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 20, 151, 51));
        gridLayout_3 = new QGridLayout(layoutWidget_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(1);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        observedXEdit_2 = new QTextEdit(layoutWidget_2);
        observedXEdit_2->setObjectName(QString::fromUtf8("observedXEdit_2"));
        observedXEdit_2->setMaximumSize(QSize(40, 40));
        observedXEdit_2->setReadOnly(true);

        gridLayout_3->addWidget(observedXEdit_2, 0, 0, 1, 1);

        observedZEdit_2 = new QTextEdit(layoutWidget_2);
        observedZEdit_2->setObjectName(QString::fromUtf8("observedZEdit_2"));
        observedZEdit_2->setMaximumSize(QSize(40, 40));
        observedZEdit_2->setReadOnly(true);

        gridLayout_3->addWidget(observedZEdit_2, 0, 2, 1, 1);

        observedYEdit_2 = new QTextEdit(layoutWidget_2);
        observedYEdit_2->setObjectName(QString::fromUtf8("observedYEdit_2"));
        observedYEdit_2->setMaximumSize(QSize(40, 40));
        observedYEdit_2->setReadOnly(true);

        gridLayout_3->addWidget(observedYEdit_2, 0, 1, 1, 1);

        layoutWidget2 = new QWidget(observedFocusGroup);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 20, 151, 51));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(1);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        observedXEdit = new QTextEdit(layoutWidget2);
        observedXEdit->setObjectName(QString::fromUtf8("observedXEdit"));
        observedXEdit->setMaximumSize(QSize(40, 40));
        observedXEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        observedXEdit->setReadOnly(true);

        gridLayout->addWidget(observedXEdit, 0, 0, 1, 1);

        observedZEdit = new QTextEdit(layoutWidget2);
        observedZEdit->setObjectName(QString::fromUtf8("observedZEdit"));
        observedZEdit->setMaximumSize(QSize(40, 40));
        observedZEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        observedZEdit->setReadOnly(true);

        gridLayout->addWidget(observedZEdit, 0, 2, 1, 1);

        observedYEdit = new QTextEdit(layoutWidget2);
        observedYEdit->setObjectName(QString::fromUtf8("observedYEdit"));
        observedYEdit->setMaximumSize(QSize(40, 40));
        observedYEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        observedYEdit->setReadOnly(true);

        gridLayout->addWidget(observedYEdit, 0, 1, 1, 1);

        desiredFocusGroup = new QGroupBox(MuseTargetingViewClass);
        desiredFocusGroup->setObjectName(QString::fromUtf8("desiredFocusGroup"));
        desiredFocusGroup->setGeometry(QRect(300, 20, 161, 81));
        desiredFocusGroup->setMaximumSize(QSize(16777210, 16777215));
        desiredFocusGroup->setAlignment(Qt::AlignCenter);
        layoutWidget3 = new QWidget(desiredFocusGroup);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 20, 151, 51));
        gridLayout_2 = new QGridLayout(layoutWidget3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(1);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        desiredXEdit = new QTextEdit(layoutWidget3);
        desiredXEdit->setObjectName(QString::fromUtf8("desiredXEdit"));
        desiredXEdit->setMaximumSize(QSize(40, 40));
        desiredXEdit->setReadOnly(false);

        gridLayout_2->addWidget(desiredXEdit, 0, 0, 1, 1);

        desiredZEdit = new QTextEdit(layoutWidget3);
        desiredZEdit->setObjectName(QString::fromUtf8("desiredZEdit"));
        desiredZEdit->setMaximumSize(QSize(40, 40));
        desiredZEdit->setReadOnly(false);

        gridLayout_2->addWidget(desiredZEdit, 0, 2, 1, 1);

        desiredYEdit = new QTextEdit(layoutWidget3);
        desiredYEdit->setObjectName(QString::fromUtf8("desiredYEdit"));
        desiredYEdit->setMaximumSize(QSize(40, 40));
        desiredYEdit->setReadOnly(false);

        gridLayout_2->addWidget(desiredYEdit, 0, 1, 1, 1);

        calibrationGroup = new QGroupBox(MuseTargetingViewClass);
        calibrationGroup->setObjectName(QString::fromUtf8("calibrationGroup"));
        calibrationGroup->setGeometry(QRect(50, 330, 161, 76));
        calibrationGroup->setMaximumSize(QSize(16777210, 16777215));
        calibrationGroup->setAlignment(Qt::AlignCenter);
        layoutWidget_3 = new QWidget(calibrationGroup);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(0, 20, 151, 51));
        gridLayout_4 = new QGridLayout(layoutWidget_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(1);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        calibrationXEdit = new QTextEdit(layoutWidget_3);
        calibrationXEdit->setObjectName(QString::fromUtf8("calibrationXEdit"));
        calibrationXEdit->setMaximumSize(QSize(40, 40));
        calibrationXEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        calibrationXEdit->setReadOnly(true);

        gridLayout_4->addWidget(calibrationXEdit, 0, 0, 1, 1);

        calibrationZEdit = new QTextEdit(layoutWidget_3);
        calibrationZEdit->setObjectName(QString::fromUtf8("calibrationZEdit"));
        calibrationZEdit->setMaximumSize(QSize(40, 40));
        calibrationZEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        calibrationZEdit->setReadOnly(true);

        gridLayout_4->addWidget(calibrationZEdit, 0, 2, 1, 1);

        calibrationYEdit = new QTextEdit(layoutWidget_3);
        calibrationYEdit->setObjectName(QString::fromUtf8("calibrationYEdit"));
        calibrationYEdit->setMaximumSize(QSize(40, 40));
        calibrationYEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        calibrationYEdit->setReadOnly(true);

        gridLayout_4->addWidget(calibrationYEdit, 0, 1, 1, 1);

        theoreticalFocusGroup = new QGroupBox(MuseTargetingViewClass);
        theoreticalFocusGroup->setObjectName(QString::fromUtf8("theoreticalFocusGroup"));
        theoreticalFocusGroup->setGeometry(QRect(50, 410, 161, 76));
        theoreticalFocusGroup->setMaximumSize(QSize(16777210, 16777215));
        theoreticalFocusGroup->setAlignment(Qt::AlignCenter);
        layoutWidget_4 = new QWidget(theoreticalFocusGroup);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(0, 20, 151, 51));
        gridLayout_5 = new QGridLayout(layoutWidget_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(1);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        theoreticalXEdit = new QTextEdit(layoutWidget_4);
        theoreticalXEdit->setObjectName(QString::fromUtf8("theoreticalXEdit"));
        theoreticalXEdit->setMaximumSize(QSize(40, 40));
        theoreticalXEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        theoreticalXEdit->setReadOnly(true);

        gridLayout_5->addWidget(theoreticalXEdit, 0, 0, 1, 1);

        theoreticalZEdit = new QTextEdit(layoutWidget_4);
        theoreticalZEdit->setObjectName(QString::fromUtf8("theoreticalZEdit"));
        theoreticalZEdit->setMaximumSize(QSize(40, 40));
        theoreticalZEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        theoreticalZEdit->setReadOnly(true);

        gridLayout_5->addWidget(theoreticalZEdit, 0, 2, 1, 1);

        theoreticalYEdit = new QTextEdit(layoutWidget_4);
        theoreticalYEdit->setObjectName(QString::fromUtf8("theoreticalYEdit"));
        theoreticalYEdit->setMaximumSize(QSize(40, 40));
        theoreticalYEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);"));
        theoreticalYEdit->setReadOnly(true);

        gridLayout_5->addWidget(theoreticalYEdit, 0, 1, 1, 1);

        resetButton = new QPushButton(MuseTargetingViewClass);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(340, 400, 75, 23));

        retranslateUi(MuseTargetingViewClass);

        QMetaObject::connectSlotsByName(MuseTargetingViewClass);
    } // setupUi

    void retranslateUi(QWidget *MuseTargetingViewClass)
    {
        MuseTargetingViewClass->setWindowTitle(QCoreApplication::translate("MuseTargetingViewClass", "Muse System Targeting", nullptr));
        currentSettingsGroup->setTitle(QCoreApplication::translate("MuseTargetingViewClass", "Current System Settings", nullptr));
        currentPsiLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "Psi", nullptr));
        currentThetaLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "Theta", nullptr));
        currentAlphaLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "Alpha", nullptr));
        currentLSliderLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "L-Slider", nullptr));
        currentXTrolleyLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "X-Trolley", nullptr));
        currentZTrolleyLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "Z-Trolley", nullptr));
        currentSettingButton->setText(QCoreApplication::translate("MuseTargetingViewClass", "Enter", nullptr));
        suggestedSettingsGroup->setTitle(QCoreApplication::translate("MuseTargetingViewClass", "Suggested System Settings", nullptr));
        suggestedPsiLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "Psi", nullptr));
        suggestedThetaLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "Theta", nullptr));
        suggestedAlphaLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "Alpha", nullptr));
        suggestedLSliderLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "L-Slider", nullptr));
        suggestedXTrolleyLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "X-Trolley", nullptr));
        suggestedZTrolleyLabel->setText(QCoreApplication::translate("MuseTargetingViewClass", "Z-Trolley", nullptr));
        calculateButton->setText(QCoreApplication::translate("MuseTargetingViewClass", "Calculate", nullptr));
        observedFocusGroup->setTitle(QCoreApplication::translate("MuseTargetingViewClass", "Observed Focus (mm, +LPH)", nullptr));
        observedFocusGroup_3->setTitle(QCoreApplication::translate("MuseTargetingViewClass", "Observed Focus (mm, +LPH)", nullptr));
        observedYEdit_2->setHtml(QCoreApplication::translate("MuseTargetingViewClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        observedYEdit->setHtml(QCoreApplication::translate("MuseTargetingViewClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        desiredFocusGroup->setTitle(QCoreApplication::translate("MuseTargetingViewClass", "Desired Focus (mm, +LPH)", nullptr));
        desiredYEdit->setHtml(QCoreApplication::translate("MuseTargetingViewClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        calibrationGroup->setTitle(QCoreApplication::translate("MuseTargetingViewClass", "Calibration (mm)", nullptr));
        calibrationXEdit->setHtml(QCoreApplication::translate("MuseTargetingViewClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        calibrationYEdit->setHtml(QCoreApplication::translate("MuseTargetingViewClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        theoreticalFocusGroup->setTitle(QCoreApplication::translate("MuseTargetingViewClass", "Theoretical Focus (mm, +LPH)", nullptr));
        theoreticalYEdit->setHtml(QCoreApplication::translate("MuseTargetingViewClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        resetButton->setText(QCoreApplication::translate("MuseTargetingViewClass", "RESET", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MuseTargetingViewClass: public Ui_MuseTargetingViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSETARGETINGVIEW_H
