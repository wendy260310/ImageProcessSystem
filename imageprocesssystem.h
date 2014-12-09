#ifndef EXPORT_DLL
#ifndef IMAGEPROCESSSYSTEM_H
#define IMAGEPROCESSSYSTEM_H
#include "OriginalImageLabel.h"
#include "header.h"
#include "setColorParametersDialog.h"
#include "ui_imageprocesssystem.h"
#include "engine.h"
class LocalEnhencementDialog;
class MatlabEngineHolder
{
public:
	static Engine * getEngine()
	{
		if(eng==NULL)
			eng=engOpen(NULL);
		return eng;
	}
private:
	class engCloser
	{
	public:
		~engCloser()
		{
			if(MatlabEngineHolder::eng)
				engClose(MatlabEngineHolder::eng);
		}
	};
	static Engine *eng;
	static engCloser closer;
};
class ImageProcessSystem : public QMainWindow
{
	Q_OBJECT
public:
	ImageProcessSystem(QWidget *parent = 0, Qt::WFlags flags = 0);
	void updateMat();
	void updateToolBar();
	void inline updateDisplayImage();
	~ImageProcessSystem();
public slots:
	void interactiveLacalEnhencementActionTriggered();
	void intercativeHighlightActionTriggered();
	void interactiveColorCorrectionActionTriggered();
	void interactiveSwitchActionTriggered();
	void interactiveFaceActionTriggered();
	void interactiveColorLevelTriggered();
	void interacitveColorBalanceTriggered();
	void interactiveColorCorrectionParametersChanged(int value);
	void interactiveLocalEnhencementParametersChanged(int value);
	void interactiveColorLevelParametersChanged(int value);
	void interativeColorBalanceParametersChanged(int value);
	void interactiveLocalEnhencementFinishSignalEmit();
	void interactiveHighlightFinishSignalEmit();
	void openFile();
	void displayColorParametersDialog();
	void saveFile();
	void faceDetectingUsingColorModel();
	void faceDetectingCombined();
	void automaticFaceDetecting();
	void automaticHighlightDetecting();
	void highlightDetection();
	void automaticHighlightRemoval();
	void automaticColorCorrection();
	void automaticLocalEnhencement();
	void setColorParameters();
	void faceMeansStatistics();
	void cancelOperation();
	void listWidgetClicked(QListWidgetItem *item);
	void sharpEffect();
	void batchHighlightRemoval();
	void superPixelActionTriggered();
private:
	void inline resetStatus();
	bool colorCorrection();
	bool loadImage();
	void connnecting();
	void interactiveColorCorrectionConnecting();
	void interactiveLocalEnhencementConnecting();
	void insertItemIntoListWidget();
	void initMat();
	void initParameters();
	void initImageLabel();
	void clearImgaes();
	//face location
	Rect face;
	MatWrapper<uchar> highlightMask;
	vector<QString> fileNames;
	//used for cancel operation
	stack<QImage> images;
	int redMeans,greenMeans,blueMeans;
	int tolerance,featherRadius;
	MatWrapper<uchar> faceMask;
	//this mat is used for region extraction,ref:BaseOperation::regionExtraction
	MatWrapper<uchar> regionMask;
	MatWrapper<Vec3b> srcMat;
	MatWrapper<Vec3b> resultMat;
	MatWrapper<Vec3f> srcHSVMat;
	QImage srcImage,resultImage;
	QString fileName;
	setColorParametersDialog paraDialog;
	Ui::ImageProcessSystemClass ui;
	//main for face detection and highlight detection
	unsigned char processStatus;
	//which interactive button is active
	unsigned char interactiveStatus;
	//face mask and highlight mask is improper
	bool currentDisplayImageImproper;
	//interactive Option
	QWidget *interactiveOptionWidget;
	OriginalImageLabel *ImageLabel;
	//new operator on interactiveOptionWidget
	bool interactiveOptionWidgetHasInit;
	//updateMat or not
	bool interactiveHasProduceResult;
};
#endif // IMAGEPROCESSSYSTEM_H
#endif