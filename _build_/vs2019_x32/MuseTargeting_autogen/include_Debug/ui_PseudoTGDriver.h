/********************************************************************************
** Form generated from reading UI file 'PseudoTGDriver.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PSEUDOTGDRIVER_H
#define UI_PSEUDOTGDRIVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PseudoTGDriver
{
public:
    QGroupBox *groupBox;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QTextEdit *pseudoTGObservedXEdit;
    QTextEdit *pseudoTGObservedYEdit;
    QTextEdit *pseudoTGObservedZEdit;
    QPushButton *pseudoTGSendButton;

    void setupUi(QWidget *PseudoTGDriver)
    {
        if (PseudoTGDriver->objectName().isEmpty())
            PseudoTGDriver->setObjectName(QString::fromUtf8("PseudoTGDriver"));
        PseudoTGDriver->resize(362, 196);
        groupBox = new QGroupBox(PseudoTGDriver);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(70, 40, 191, 101));
        groupBox->setAlignment(Qt::AlignCenter);
        splitter = new QSplitter(groupBox);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(30, 20, 134, 65));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pseudoTGObservedXEdit = new QTextEdit(layoutWidget);
        pseudoTGObservedXEdit->setObjectName(QString::fromUtf8("pseudoTGObservedXEdit"));
        pseudoTGObservedXEdit->setMaximumSize(QSize(40, 40));
        pseudoTGObservedXEdit->setReadOnly(false);

        gridLayout->addWidget(pseudoTGObservedXEdit, 0, 0, 1, 1);

        pseudoTGObservedYEdit = new QTextEdit(layoutWidget);
        pseudoTGObservedYEdit->setObjectName(QString::fromUtf8("pseudoTGObservedYEdit"));
        pseudoTGObservedYEdit->setMaximumSize(QSize(40, 40));
        pseudoTGObservedYEdit->setReadOnly(false);

        gridLayout->addWidget(pseudoTGObservedYEdit, 0, 1, 1, 1);

        pseudoTGObservedZEdit = new QTextEdit(layoutWidget);
        pseudoTGObservedZEdit->setObjectName(QString::fromUtf8("pseudoTGObservedZEdit"));
        pseudoTGObservedZEdit->setMaximumSize(QSize(40, 40));
        pseudoTGObservedZEdit->setReadOnly(false);

        gridLayout->addWidget(pseudoTGObservedZEdit, 0, 2, 1, 1);

        splitter->addWidget(layoutWidget);
        pseudoTGSendButton = new QPushButton(splitter);
        pseudoTGSendButton->setObjectName(QString::fromUtf8("pseudoTGSendButton"));
        splitter->addWidget(pseudoTGSendButton);

        retranslateUi(PseudoTGDriver);

        QMetaObject::connectSlotsByName(PseudoTGDriver);
    } // setupUi

    void retranslateUi(QWidget *PseudoTGDriver)
    {
        PseudoTGDriver->setWindowTitle(QCoreApplication::translate("PseudoTGDriver", "Pseudo-Thermoguide", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PseudoTGDriver", "Enter Observed Focus (mm, +LPH)", nullptr));
        pseudoTGObservedYEdit->setHtml(QCoreApplication::translate("PseudoTGDriver", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pseudoTGSendButton->setText(QCoreApplication::translate("PseudoTGDriver", "Send to Muse Targeting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PseudoTGDriver: public Ui_PseudoTGDriver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PSEUDOTGDRIVER_H
