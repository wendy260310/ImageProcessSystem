/********************************************************************************
** Form generated from reading UI file 'imageprocesssystem.ui'
**
** Created: Thu Dec 18 14:24:35 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESSSYSTEM_H
#define UI_IMAGEPROCESSSYSTEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessSystemClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionColorCorrection;
    QAction *faceDetectingColorModelAction;
    QAction *faceDetectingCombineAction;
    QAction *actionFace;
    QAction *actionHighLightDetection;
    QAction *setColorParametersAction;
    QAction *actionHighlightRemoval;
    QAction *actionCancel;
    QAction *faceMeansStatisticsAction;
    QAction *sharpenAction;
    QAction *highlightBatchAction;
    QAction *actionInteractiveLocalEnhencement;
    QAction *actionInteractiveColorCorrection;
    QAction *actionSwitch;
    QAction *actionInteractiveHighlight;
    QAction *actionInteractiveFace;
    QAction *actionInteractiveColorLevel;
    QAction *actionInteractiveColorBalance;
    QAction *actionSuperPixel;
    QAction *actionInteractiveTriangle;
    QAction *actionTriangle;
    QAction *actionMeshEditing;
    QWidget *centralWidget;
    QLabel *pixelValueLabel;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QMenu *menu_Tools;
    QMenu *faceDetetingMenu;
    QMenu *menu_Settings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageProcessSystemClass)
    {
        if (ImageProcessSystemClass->objectName().isEmpty())
            ImageProcessSystemClass->setObjectName(QString::fromUtf8("ImageProcessSystemClass"));
        ImageProcessSystemClass->setEnabled(true);
        ImageProcessSystemClass->resize(1061, 727);
        actionOpen = new QAction(ImageProcessSystemClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave = new QAction(ImageProcessSystemClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pictures/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionColorCorrection = new QAction(ImageProcessSystemClass);
        actionColorCorrection->setObjectName(QString::fromUtf8("actionColorCorrection"));
        actionColorCorrection->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/pictures/autocolorcorrection.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionColorCorrection->setIcon(icon2);
        faceDetectingColorModelAction = new QAction(ImageProcessSystemClass);
        faceDetectingColorModelAction->setObjectName(QString::fromUtf8("faceDetectingColorModelAction"));
        faceDetectingCombineAction = new QAction(ImageProcessSystemClass);
        faceDetectingCombineAction->setObjectName(QString::fromUtf8("faceDetectingCombineAction"));
        actionFace = new QAction(ImageProcessSystemClass);
        actionFace->setObjectName(QString::fromUtf8("actionFace"));
        actionFace->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/pictures/face.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionFace->setIcon(icon3);
        actionHighLightDetection = new QAction(ImageProcessSystemClass);
        actionHighLightDetection->setObjectName(QString::fromUtf8("actionHighLightDetection"));
        actionHighLightDetection->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/pictures/highlight.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHighLightDetection->setIcon(icon4);
        setColorParametersAction = new QAction(ImageProcessSystemClass);
        setColorParametersAction->setObjectName(QString::fromUtf8("setColorParametersAction"));
        actionHighlightRemoval = new QAction(ImageProcessSystemClass);
        actionHighlightRemoval->setObjectName(QString::fromUtf8("actionHighlightRemoval"));
        actionHighlightRemoval->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/pictures/highlightremoval.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHighlightRemoval->setIcon(icon5);
        actionCancel = new QAction(ImageProcessSystemClass);
        actionCancel->setObjectName(QString::fromUtf8("actionCancel"));
        actionCancel->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/pictures/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCancel->setIcon(icon6);
        faceMeansStatisticsAction = new QAction(ImageProcessSystemClass);
        faceMeansStatisticsAction->setObjectName(QString::fromUtf8("faceMeansStatisticsAction"));
        faceMeansStatisticsAction->setEnabled(false);
        sharpenAction = new QAction(ImageProcessSystemClass);
        sharpenAction->setObjectName(QString::fromUtf8("sharpenAction"));
        sharpenAction->setEnabled(false);
        highlightBatchAction = new QAction(ImageProcessSystemClass);
        highlightBatchAction->setObjectName(QString::fromUtf8("highlightBatchAction"));
        actionInteractiveLocalEnhencement = new QAction(ImageProcessSystemClass);
        actionInteractiveLocalEnhencement->setObjectName(QString::fromUtf8("actionInteractiveLocalEnhencement"));
        actionInteractiveLocalEnhencement->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/pictures/localenhencementnotselected.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionInteractiveLocalEnhencement->setIcon(icon7);
        actionInteractiveColorCorrection = new QAction(ImageProcessSystemClass);
        actionInteractiveColorCorrection->setObjectName(QString::fromUtf8("actionInteractiveColorCorrection"));
        actionInteractiveColorCorrection->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/pictures/colorcorrectnotselected.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionInteractiveColorCorrection->setIcon(icon8);
        actionSwitch = new QAction(ImageProcessSystemClass);
        actionSwitch->setObjectName(QString::fromUtf8("actionSwitch"));
        actionSwitch->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/pictures/switch.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSwitch->setIcon(icon9);
        actionInteractiveHighlight = new QAction(ImageProcessSystemClass);
        actionInteractiveHighlight->setObjectName(QString::fromUtf8("actionInteractiveHighlight"));
        actionInteractiveHighlight->setEnabled(false);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/pictures/highlightnotselected.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionInteractiveHighlight->setIcon(icon10);
        actionInteractiveFace = new QAction(ImageProcessSystemClass);
        actionInteractiveFace->setObjectName(QString::fromUtf8("actionInteractiveFace"));
        actionInteractiveFace->setEnabled(false);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/pictures/facenotselected.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionInteractiveFace->setIcon(icon11);
        actionInteractiveColorLevel = new QAction(ImageProcessSystemClass);
        actionInteractiveColorLevel->setObjectName(QString::fromUtf8("actionInteractiveColorLevel"));
        actionInteractiveColorLevel->setEnabled(false);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/pictures/colorlevelnotselected.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionInteractiveColorLevel->setIcon(icon12);
        actionInteractiveColorBalance = new QAction(ImageProcessSystemClass);
        actionInteractiveColorBalance->setObjectName(QString::fromUtf8("actionInteractiveColorBalance"));
        actionInteractiveColorBalance->setEnabled(false);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/pictures/colorbalancenotselected.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionInteractiveColorBalance->setIcon(icon13);
        actionSuperPixel = new QAction(ImageProcessSystemClass);
        actionSuperPixel->setObjectName(QString::fromUtf8("actionSuperPixel"));
        actionSuperPixel->setEnabled(false);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/pictures/superpixel.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSuperPixel->setIcon(icon14);
        actionInteractiveTriangle = new QAction(ImageProcessSystemClass);
        actionInteractiveTriangle->setObjectName(QString::fromUtf8("actionInteractiveTriangle"));
        actionInteractiveTriangle->setEnabled(false);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/pictures/trianglnoteselected.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionInteractiveTriangle->setIcon(icon15);
        actionTriangle = new QAction(ImageProcessSystemClass);
        actionTriangle->setObjectName(QString::fromUtf8("actionTriangle"));
        actionTriangle->setEnabled(false);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/pictures/triangleicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionTriangle->setIcon(icon16);
        actionMeshEditing = new QAction(ImageProcessSystemClass);
        actionMeshEditing->setObjectName(QString::fromUtf8("actionMeshEditing"));
        actionMeshEditing->setEnabled(false);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/pictures/mesheditingnotselected.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionMeshEditing->setIcon(icon17);
        centralWidget = new QWidget(ImageProcessSystemClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        pixelValueLabel = new QLabel(centralWidget);
        pixelValueLabel->setObjectName(QString::fromUtf8("pixelValueLabel"));
        pixelValueLabel->setGeometry(QRect(420, 520, 102, 12));
        pixelValueLabel->setAlignment(Qt::AlignCenter);
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 164, 624));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ImageProcessSystemClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageProcessSystemClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1061, 23));
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
        menu_Tools->setEnabled(true);
        faceDetetingMenu = new QMenu(menu_Tools);
        faceDetetingMenu->setObjectName(QString::fromUtf8("faceDetetingMenu"));
        faceDetetingMenu->setEnabled(false);
        menu_Settings = new QMenu(menuBar);
        menu_Settings->setObjectName(QString::fromUtf8("menu_Settings"));
        ImageProcessSystemClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageProcessSystemClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setIconSize(QSize(48, 48));
        ImageProcessSystemClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageProcessSystemClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(false);
        ImageProcessSystemClass->setStatusBar(statusBar);

        menuBar->addAction(menu_Tools->menuAction());
        menuBar->addAction(menu_Settings->menuAction());
        menu_Tools->addAction(faceDetetingMenu->menuAction());
        menu_Tools->addAction(faceMeansStatisticsAction);
        menu_Tools->addAction(sharpenAction);
        menu_Tools->addAction(highlightBatchAction);
        faceDetetingMenu->addAction(faceDetectingColorModelAction);
        faceDetetingMenu->addAction(faceDetectingCombineAction);
        menu_Settings->addAction(setColorParametersAction);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionColorCorrection);
        mainToolBar->addAction(actionFace);
        mainToolBar->addAction(actionHighLightDetection);
        mainToolBar->addAction(actionHighlightRemoval);
        mainToolBar->addAction(actionSuperPixel);
        mainToolBar->addAction(actionTriangle);
        mainToolBar->addAction(actionCancel);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionInteractiveLocalEnhencement);
        mainToolBar->addAction(actionInteractiveColorCorrection);
        mainToolBar->addAction(actionInteractiveHighlight);
        mainToolBar->addAction(actionInteractiveFace);
        mainToolBar->addAction(actionInteractiveColorLevel);
        mainToolBar->addAction(actionInteractiveColorBalance);
        mainToolBar->addAction(actionInteractiveTriangle);
        mainToolBar->addAction(actionMeshEditing);
        mainToolBar->addAction(actionSwitch);

        retranslateUi(ImageProcessSystemClass);

        QMetaObject::connectSlotsByName(ImageProcessSystemClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageProcessSystemClass)
    {
        ImageProcessSystemClass->setWindowTitle(QApplication::translate("ImageProcessSystemClass", "ImageProcessSystem", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("ImageProcessSystemClass", "\346\211\223\345\274\200\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("ImageProcessSystemClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        actionColorCorrection->setText(QApplication::translate("ImageProcessSystemClass", "\350\207\252\345\212\250\350\211\262\345\275\251", 0, QApplication::UnicodeUTF8));
        faceDetectingColorModelAction->setText(QApplication::translate("ImageProcessSystemClass", "\350\211\262\345\275\251\346\250\241\345\236\213", 0, QApplication::UnicodeUTF8));
        faceDetectingCombineAction->setText(QApplication::translate("ImageProcessSystemClass", "&Combine", 0, QApplication::UnicodeUTF8));
        actionFace->setText(QApplication::translate("ImageProcessSystemClass", "\344\272\272\350\204\270\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        actionHighLightDetection->setText(QApplication::translate("ImageProcessSystemClass", "\351\253\230\345\205\211\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        setColorParametersAction->setText(QApplication::translate("ImageProcessSystemClass", "\344\272\272\350\204\270\350\202\244\350\211\262\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        actionHighlightRemoval->setText(QApplication::translate("ImageProcessSystemClass", "\351\253\230\345\205\211\345\216\273\351\231\244", 0, QApplication::UnicodeUTF8));
        actionCancel->setText(QApplication::translate("ImageProcessSystemClass", "\344\270\212\344\270\200\346\255\245", 0, QApplication::UnicodeUTF8));
        faceMeansStatisticsAction->setText(QApplication::translate("ImageProcessSystemClass", "\350\204\270\351\203\250\345\235\207\345\200\274\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
        sharpenAction->setText(QApplication::translate("ImageProcessSystemClass", "\351\224\220\345\214\226", 0, QApplication::UnicodeUTF8));
        highlightBatchAction->setText(QApplication::translate("ImageProcessSystemClass", "\351\253\230\345\205\211\346\211\271\345\244\204\347\220\206", 0, QApplication::UnicodeUTF8));
        actionInteractiveLocalEnhencement->setText(QApplication::translate("ImageProcessSystemClass", "\345\261\200\351\203\250\344\272\244\344\272\222", 0, QApplication::UnicodeUTF8));
        actionInteractiveColorCorrection->setText(QApplication::translate("ImageProcessSystemClass", "\350\211\262\345\275\251\344\272\244\344\272\222", 0, QApplication::UnicodeUTF8));
        actionSwitch->setText(QApplication::translate("ImageProcessSystemClass", "\345\210\207\346\215\242\357\274\214\344\272\244\344\272\222\345\256\214\344\272\206\347\202\271\350\277\231\344\270\252\344\277\235\345\255\230\357\274\201", 0, QApplication::UnicodeUTF8));
        actionInteractiveHighlight->setText(QApplication::translate("ImageProcessSystemClass", "\346\232\202\346\227\266\344\270\215\350\246\201\347\224\250", 0, QApplication::UnicodeUTF8));
        actionInteractiveFace->setText(QApplication::translate("ImageProcessSystemClass", "InteractiveFace", 0, QApplication::UnicodeUTF8));
        actionInteractiveColorLevel->setText(QApplication::translate("ImageProcessSystemClass", "InteractiveColorLevel", 0, QApplication::UnicodeUTF8));
        actionInteractiveColorBalance->setText(QApplication::translate("ImageProcessSystemClass", "InteractiveColorBalance", 0, QApplication::UnicodeUTF8));
        actionSuperPixel->setText(QApplication::translate("ImageProcessSystemClass", "SuperPixel", 0, QApplication::UnicodeUTF8));
        actionInteractiveTriangle->setText(QApplication::translate("ImageProcessSystemClass", "InteractiveTriangle", 0, QApplication::UnicodeUTF8));
        actionTriangle->setText(QApplication::translate("ImageProcessSystemClass", "Triangle", 0, QApplication::UnicodeUTF8));
        actionMeshEditing->setText(QApplication::translate("ImageProcessSystemClass", "MeshEditing", 0, QApplication::UnicodeUTF8));
        pixelValueLabel->setText(QString());
        menu_Tools->setTitle(QApplication::translate("ImageProcessSystemClass", "&Tools", 0, QApplication::UnicodeUTF8));
        faceDetetingMenu->setTitle(QApplication::translate("ImageProcessSystemClass", "\344\272\272\350\204\270\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        menu_Settings->setTitle(QApplication::translate("ImageProcessSystemClass", "&Settings", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessSystemClass: public Ui_ImageProcessSystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSSYSTEM_H
