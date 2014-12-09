/********************************************************************************
** Form generated from reading UI file 'HighlightInteractiveDialog.ui'
**
** Created: Sat Jun 28 10:36:22 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIGHLIGHTINTERACTIVEDIALOG_H
#define UI_HIGHLIGHTINTERACTIVEDIALOG_H

#include <InteractiveImageLabel.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *cancelButton;
    QPushButton *okButton;
    InteractiveImageLabel *label;
    QGroupBox *groupBox;
    QRadioButton *BrushRadioButton;
    QRadioButton *thresholdRadioButton;
    QSlider *threshSlider;
    QLabel *thresholdLabel;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(822, 738);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(280, 660, 158, 25));
        hboxLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        label = new InteractiveImageLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 80, 411, 471));
        label->setMouseTracking(false);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(620, 200, 171, 170));
        BrushRadioButton = new QRadioButton(groupBox);
        BrushRadioButton->setObjectName(QString::fromUtf8("BrushRadioButton"));
        BrushRadioButton->setGeometry(QRect(40, 20, 53, 16));
        thresholdRadioButton = new QRadioButton(groupBox);
        thresholdRadioButton->setObjectName(QString::fromUtf8("thresholdRadioButton"));
        thresholdRadioButton->setGeometry(QRect(40, 60, 77, 16));
        thresholdRadioButton->setChecked(true);
        threshSlider = new QSlider(groupBox);
        threshSlider->setObjectName(QString::fromUtf8("threshSlider"));
        threshSlider->setGeometry(QRect(40, 100, 91, 19));
        threshSlider->setOrientation(Qt::Horizontal);
        thresholdLabel = new QLabel(groupBox);
        thresholdLabel->setObjectName(QString::fromUtf8("thresholdLabel"));
        thresholdLabel->setGeometry(QRect(50, 130, 71, 20));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("Dialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("Dialog", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        groupBox->setTitle(QApplication::translate("Dialog", "options", 0, QApplication::UnicodeUTF8));
        BrushRadioButton->setText(QApplication::translate("Dialog", "Brush", 0, QApplication::UnicodeUTF8));
        thresholdRadioButton->setText(QApplication::translate("Dialog", "threshold", 0, QApplication::UnicodeUTF8));
        thresholdLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIGHLIGHTINTERACTIVEDIALOG_H
