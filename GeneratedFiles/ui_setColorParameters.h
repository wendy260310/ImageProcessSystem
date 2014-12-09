/********************************************************************************
** Form generated from reading UI file 'setColorParameters.ui'
**
** Created: Tue Nov 25 09:08:27 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCOLORPARAMETERS_H
#define UI_SETCOLORPARAMETERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_colorParametersDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSlider *brightnessSlider;
    QSlider *redSlider;
    QSlider *yellowSlider;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *brightnessLabel;
    QLabel *redLabel;
    QLabel *yellowLabel;
    QLabel *label_10;
    QLineEdit *toleranceLineEdit;
    QLineEdit *featherLineEdit;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QDialog *colorParametersDialog)
    {
        if (colorParametersDialog->objectName().isEmpty())
            colorParametersDialog->setObjectName(QString::fromUtf8("colorParametersDialog"));
        colorParametersDialog->resize(400, 408);
        layoutWidget = new QWidget(colorParametersDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 360, 351, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        brightnessSlider = new QSlider(colorParametersDialog);
        brightnessSlider->setObjectName(QString::fromUtf8("brightnessSlider"));
        brightnessSlider->setGeometry(QRect(110, 50, 160, 19));
        brightnessSlider->setMinimum(170);
        brightnessSlider->setMaximum(190);
        brightnessSlider->setSliderPosition(175);
        brightnessSlider->setOrientation(Qt::Horizontal);
        redSlider = new QSlider(colorParametersDialog);
        redSlider->setObjectName(QString::fromUtf8("redSlider"));
        redSlider->setGeometry(QRect(110, 130, 160, 19));
        redSlider->setMinimum(116);
        redSlider->setMaximum(129);
        redSlider->setSliderPosition(120);
        redSlider->setOrientation(Qt::Horizontal);
        yellowSlider = new QSlider(colorParametersDialog);
        yellowSlider->setObjectName(QString::fromUtf8("yellowSlider"));
        yellowSlider->setGeometry(QRect(110, 210, 160, 19));
        yellowSlider->setMinimum(103);
        yellowSlider->setMaximum(116);
        yellowSlider->setValue(110);
        yellowSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(colorParametersDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 30, 24, 12));
        label_2 = new QLabel(colorParametersDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 110, 54, 12));
        label_3 = new QLabel(colorParametersDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(160, 190, 66, 12));
        label_4 = new QLabel(colorParametersDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 50, 18, 12));
        label_5 = new QLabel(colorParametersDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 50, 18, 12));
        label_6 = new QLabel(colorParametersDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(80, 130, 18, 12));
        label_7 = new QLabel(colorParametersDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(280, 130, 18, 12));
        label_8 = new QLabel(colorParametersDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(80, 210, 18, 12));
        label_9 = new QLabel(colorParametersDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(280, 210, 18, 12));
        brightnessLabel = new QLabel(colorParametersDialog);
        brightnessLabel->setObjectName(QString::fromUtf8("brightnessLabel"));
        brightnessLabel->setGeometry(QRect(180, 80, 18, 12));
        redLabel = new QLabel(colorParametersDialog);
        redLabel->setObjectName(QString::fromUtf8("redLabel"));
        redLabel->setGeometry(QRect(180, 160, 18, 12));
        yellowLabel = new QLabel(colorParametersDialog);
        yellowLabel->setObjectName(QString::fromUtf8("yellowLabel"));
        yellowLabel->setGeometry(QRect(180, 240, 18, 12));
        label_10 = new QLabel(colorParametersDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(160, 10, 72, 12));
        toleranceLineEdit = new QLineEdit(colorParametersDialog);
        toleranceLineEdit->setObjectName(QString::fromUtf8("toleranceLineEdit"));
        toleranceLineEdit->setGeometry(QRect(60, 270, 113, 20));
        featherLineEdit = new QLineEdit(colorParametersDialog);
        featherLineEdit->setObjectName(QString::fromUtf8("featherLineEdit"));
        featherLineEdit->setGeometry(QRect(220, 270, 113, 20));
        label_11 = new QLabel(colorParametersDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(90, 300, 54, 12));
        label_12 = new QLabel(colorParametersDialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(260, 300, 42, 12));

        retranslateUi(colorParametersDialog);
        QObject::connect(okButton, SIGNAL(clicked()), colorParametersDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), colorParametersDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(colorParametersDialog);
    } // setupUi

    void retranslateUi(QDialog *colorParametersDialog)
    {
        colorParametersDialog->setWindowTitle(QApplication::translate("colorParametersDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("colorParametersDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("colorParametersDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("colorParametersDialog", "\344\272\256\345\272\246", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("colorParametersDialog", "data1(\347\272\242)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("colorParametersDialog", "data4(\350\223\235\351\273\204)", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("colorParametersDialog", "170", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("colorParametersDialog", "190", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("colorParametersDialog", "116", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("colorParametersDialog", "129", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("colorParametersDialog", "103", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("colorParametersDialog", "116", 0, QApplication::UnicodeUTF8));
        brightnessLabel->setText(QApplication::translate("colorParametersDialog", "175", 0, QApplication::UnicodeUTF8));
        redLabel->setText(QApplication::translate("colorParametersDialog", "120", 0, QApplication::UnicodeUTF8));
        yellowLabel->setText(QApplication::translate("colorParametersDialog", "110", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("colorParametersDialog", "\350\211\262\345\275\251\344\274\230\345\214\226\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        toleranceLineEdit->setText(QApplication::translate("colorParametersDialog", "32", 0, QApplication::UnicodeUTF8));
        featherLineEdit->setText(QApplication::translate("colorParametersDialog", "25", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("colorParametersDialog", "tolerance", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("colorParametersDialog", "feather", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class colorParametersDialog: public Ui_colorParametersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCOLORPARAMETERS_H
