#ifndef EXPORT_DLL
#include "imageprocesssystem.h"
#include "parameters.h"
#include "BasisOperation.h"
#include "highlightDetection.h"
#include "faceDetector.h"
#include "ColorCorrection.h"
#include "highlightRemoval.h"
#include "InteractiveHighlightWidget.h"
#include "ColorSpaceTransitionClass.h"
#include "LocalEnhencementLabel.h"
#include "HighlightLabel.h"
#include "InteractiveFaceLabel.h"
#include "InteractiveColorLevel.h"
#include "InteractiveColorBalanceWidget.h"

#include "InteractiveLocalEnhencementWidget.h"
#include "InteractiveColorCorrectionWidget.h"
#include "SLIC.h"
Engine * MatlabEngineHolder::eng=NULL;
ImageProcessSystem::ImageProcessSystem(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	connnecting();
	initParameters();
#ifdef DEMO
	ui.actionOpen->setEnabled(false);
#endif
}
void ImageProcessSystem::initParameters()
{
	blueMeans=141;
	greenMeans=157;
	redMeans=197;
	tolerance=32;
	featherRadius=25;
	ui.listWidget->setIconSize(QSize(280,195));
	currentDisplayImageImproper=true;
	resetStatus();
	interactiveOptionWidget=NULL;
	ImageLabel=NULL;
	interactiveOptionWidgetHasInit=false;
	interactiveHasProduceResult=false;
	faceDetector::loadCascade();
}
ImageProcessSystem::~ImageProcessSystem()
{
	delete interactiveOptionWidget;
	delete ImageLabel;
}
void ImageProcessSystem::connnecting()
{
	connect(ui.actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));
	connect(ui.faceDetectingColorModelAction,SIGNAL(triggered()),this,SLOT(faceDetectingUsingColorModel()));
	connect(ui.faceDetectingCombineAction,SIGNAL(triggered()),this,SLOT(faceDetectingCombined()));
	connect(ui.actionColorCorrection,SIGNAL(triggered()),this,SLOT(automaticColorCorrection()));
	connect(ui.actionFace,SIGNAL(triggered()),this,SLOT(automaticFaceDetecting()));
	connect(ui.actionHighLightDetection,SIGNAL(triggered()),this,SLOT(automaticHighlightDetecting()));
	connect(ui.setColorParametersAction,SIGNAL(triggered()),this,SLOT(displayColorParametersDialog()));
	connect(paraDialog.getOKAction(),SIGNAL(clicked()),this,SLOT(setColorParameters()));
	connect(ui.actionHighlightRemoval,SIGNAL(triggered()),this,SLOT(automaticHighlightRemoval()));
	connect(ui.listWidget,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(listWidgetClicked(QListWidgetItem *)));
	connect(ui.actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));
	connect(ui.actionCancel,SIGNAL(triggered()),this,SLOT(cancelOperation()));
	connect(ui.faceMeansStatisticsAction,SIGNAL(triggered()),this,SLOT(faceMeansStatistics()));
	connect(ui.sharpenAction,SIGNAL(triggered()),this,SLOT(sharpEffect()));
	connect(ui.highlightBatchAction,SIGNAL(triggered()),this,SLOT(batchHighlightRemoval()));
	connect(ui.actionInteractiveLocalEnhencement,SIGNAL(triggered()),this,SLOT(interactiveLacalEnhencementActionTriggered()));
	connect(ui.actionInteractiveColorCorrection,SIGNAL(triggered()),this,SLOT(interactiveColorCorrectionActionTriggered()));
	connect(ui.actionSwitch,SIGNAL(triggered()),this,SLOT(interactiveSwitchActionTriggered()));
	connect(ui.actionInteractiveHighlight,SIGNAL(triggered()),this,SLOT(intercativeHighlightActionTriggered()));
	connect(ui.actionInteractiveFace,SIGNAL(triggered()),this,SLOT(interactiveFaceActionTriggered()));
	connect(ui.actionInteractiveColorLevel,SIGNAL(triggered()),this,SLOT(interactiveColorLevelTriggered()));
	connect(ui.actionInteractiveColorBalance,SIGNAL(triggered()),this,SLOT(interacitveColorBalanceTriggered()));
	connect(ui.actionSuperPixel,SIGNAL(triggered()),this,SLOT(superPixelActionTriggered()));
}
void ImageProcessSystem::displayColorParametersDialog()
{
	paraDialog.show();
}
//please trigger macro DEMO when using this function
void ImageProcessSystem::batchHighlightRemoval()
{
	QString filePath=QFileDialog::getExistingDirectory(this,"Open Directory",QDir::currentPath());
	QDir dir(filePath);
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	dir.setSorting(QDir::Size | QDir::Reversed);
	QFileInfoList list = dir.entryInfoList();
	for(int i=0;i<list.size();++i)
	{
		const QFileInfo &fileInfo=list.at(i);
		fileName=fileInfo.absoluteFilePath();
		//file filter,but not quite well
		if(!(fileName.contains(".jpg")||fileName.contains(".JPG"))||fileName.contains("_normal")||fileName.contains("cluster"))
		{
			continue;
		}
		loadImage();
		resetStatus();
		initMat();
		fileName.remove(".jpg");
		fileName.remove(".JPG");
		fileName+="_cbcr.jpg";
	/*	highlightDetection();
		srcMat.copyTo(resultMat);
		Rect face=faceDetector::detectingFacesUsingOpencv(srcMat);
		HighLightRemoval::removal(srcMat,resultMat,highlightMask,face,HIGHLIGHT_REMOVAL_POSSION_MATHOD);
		if(!BasisOperation::faceNeedColorCorrection(resultMat,faceMask,face))
		{
			imwrite(fileName.toStdString(),resultMat);
			continue;
		}
		resultMat.copyTo(srcMat);
		colorCorrection();*/
		//srcMat.copyTo(resultMat);
		//colorCorrection();
		faceDetectingCombined();
		imwrite(fileName.toStdString(),faceMask.get());
	}
}
//discard!!
void ImageProcessSystem::faceMeansStatistics()
{
	QString filePath=QFileDialog::getExistingDirectory(this,"Open Directory",QDir::currentPath());
	QDir dir(filePath);
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	dir.setSorting(QDir::Size | QDir::Reversed);
	fstream f("D:\\a.txt");
	f<<"R"<<'\t'<<"G"<<'\t'<<"B"<<'\t'<<"data1"<<'\t'<<"data4"<<'\t'<<"brightness"<<endl;
	QFileInfoList list = dir.entryInfoList();
	double rMeans=0,gMeans=0,bMeans=0,data1Means=0,data4Means=0,brightnessMeans=0;
	for(int i=0;i<list.size();++i)
	{
		const QFileInfo &fileInfo=list.at(i);
		QString fileFullPath=fileInfo.absoluteFilePath();
		QImage src=QImage(fileFullPath);
		double R=0,G=0,B=0,data1,data4,brightness;
		Mat fMat(src.height(),src.width(),CV_8UC1);
		Mat sMat(src.height(),src.width(),CV_8UC3);
		BasisOperation::qimage2Mat(src,sMat);
		memset(fMat.data,NOTFACE_PIXEL_VALUE,src.height()*src.width()*sizeof(uchar));
		faceDetector::detectingFace(sMat,fMat,FACE_COLORMODEL|FACE_USINGOPENCV,face);
		int count=0;
		for(int j=0;j<src.width();++j)
			for(int k=0;k<src.height();++k)
			{
				if(fMat.at<uchar>(k,j)==FACE_PIXEL_VALUE)
				{
					count++;
					R+=(double)sMat.at<Vec3b>(k,j)[2];
					G+=(double)sMat.at<Vec3b>(k,j)[1];
					B+=(double)sMat.at<Vec3b>(k,j)[0];
				}
			}
		R/=count;
		G/=count;
		B/=count;
		data1=R*100/G;
		data4=G*100/B;
		brightness=0.3*R+0.59*G+0.11*B;
		f<<R<<'\t'<<B<<'\t'<<B<<'\t'<<data1<<'\t'<<data4<<'\t'<<brightness<<endl;
		rMeans+=R;
		gMeans+=G;
		bMeans+=B;
		data1Means+=data1;
		data4Means+=data4;
		brightnessMeans+=brightness;
	}
	f<<"==================="<<endl;
	rMeans/=list.size();
	gMeans/=list.size();
	bMeans/=list.size();
	data1Means/=list.size();
	data4Means/=list.size();
	brightnessMeans/=list.size();
	f<<rMeans<<'\t'<<gMeans<<'\t'<<bMeans<<'\t'<<data1Means<<'\t'<<data4Means<<'\t'<<brightnessMeans<<endl;
}
void ImageProcessSystem::setColorParameters()
{
	paraDialog.hide();
	double data1=paraDialog.getData1()*0.01;
	double data4=paraDialog.getData4()*0.01;
	double brightness=paraDialog.getBrightness();
	blueMeans=(int)(brightness/(0.3*data1*data4+0.59*data4+0.11));
	greenMeans=(int)(data4*blueMeans);
	redMeans=(int)(data1*greenMeans);
	tolerance=(paraDialog.getTolerance()==0)?32:paraDialog.getTolerance();
	featherRadius=(paraDialog.getFeather()==0)?25:paraDialog.getFeather();
}
//this slots design for menu
void ImageProcessSystem::faceDetectingUsingColorModel()
{
	if(srcImage.isNull())
		return;
	//here,only combined method triggers processStatus
	processStatus&=(~FACE_DETECTION_DONE);
	memset(faceMask.get().data,NOTFACE_PIXEL_VALUE,srcImage.width()*srcImage.height()*sizeof(uchar));
	faceDetector::detectingFace(srcMat.get(),faceMask.get(),FACE_COLORMODEL,face);
	images.push(srcImage);
#ifdef DEBUG
	imshow("faceMask",faceMask.get());
#else
	currentDisplayImageImproper=true;
	updateToolBar();
	Mat faceMaskThreeChannel;
	cvtColor(faceMask.get(),faceMaskThreeChannel,CV_GRAY2BGR);
	QImage faceMaskImage(faceMask->cols,faceMask->rows,QImage::Format_RGB32);
	BasisOperation::mat2QImage(faceMaskThreeChannel,faceMaskImage);
	ImageLabel->displayImage(faceMaskImage);
#endif
}
//for toolbar
void ImageProcessSystem::automaticFaceDetecting()
{
	faceDetectingCombined();
	images.push(srcImage);
	currentDisplayImageImproper=true;
#ifdef DEBUG
	imshow("faceMask",faceMask.get());
#else
	Mat faceMaskThreeChannel;
	cvtColor(faceMask.get(),faceMaskThreeChannel,CV_GRAY2BGR);
	QImage faceMaskImage(faceMask->cols,faceMask->rows,QImage::Format_RGB32);
	BasisOperation::mat2QImage(faceMaskThreeChannel,faceMaskImage);
	ImageLabel->displayImage(faceMaskImage);
#endif
	updateToolBar();
}
void ImageProcessSystem::interacitveColorBalanceTriggered()
{
	if(interactiveStatus&INTERACTIVE_COLOR_BALANCE_SELECTED)
		return ;
	if(interactiveHasProduceResult)
	{
		interactiveHasProduceResult=false;
		updateMat();
	}
	interactiveStatus=INTERACTIVE_COLOR_BALANCE_SELECTED;
	interactiveOptionWidgetHasInit=true;
	delete ImageLabel;
	ImageLabel=new OriginalImageLabel(ui.centralWidget);
	initImageLabel();
	delete interactiveOptionWidget;
	interactiveOptionWidget=new InteractiveColorBalanceWidget(ui.centralWidget);
	interactiveOptionWidget->setGeometry(ImageLabel->x()+ImageLabel->width()+10,ImageLabel->y(),240,ImageLabel->height());
	interactiveOptionWidget->setVisible(true);
	connect(((InteractiveColorBalanceWidget *)interactiveOptionWidget)->redSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interativeColorBalanceParametersChanged(int)));
	connect(((InteractiveColorBalanceWidget *)interactiveOptionWidget)->greenSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interativeColorBalanceParametersChanged(int)));
	connect(((InteractiveColorBalanceWidget *)interactiveOptionWidget)->blueSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interativeColorBalanceParametersChanged(int)));
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::interactiveColorLevelTriggered()
{
	if(interactiveStatus&INTERACTIVE_COLOR_LEVEL_SELECTED)
		return;
	if(interactiveHasProduceResult)
	{
		interactiveHasProduceResult=false;
		updateMat();
	}
	interactiveStatus=0;
	interactiveStatus|=INTERACTIVE_COLOR_LEVEL_SELECTED;
	delete ImageLabel;
	ImageLabel=new OriginalImageLabel(ui.centralWidget);
	initImageLabel();
	interactiveOptionWidgetHasInit=true;
	delete interactiveOptionWidget;
	interactiveOptionWidget=new InteractiveColorLevelWidget(ui.centralWidget);
	interactiveOptionWidget->setGeometry(ImageLabel->x()+ImageLabel->width()+10,ImageLabel->y(),240,ImageLabel->height());
	interactiveOptionWidget->setVisible(true);
	connect(((InteractiveColorLevelWidget *)interactiveOptionWidget)->redSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveColorLevelParametersChanged(int)));
	connect(((InteractiveColorLevelWidget *)interactiveOptionWidget)->lightnessSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveColorLevelParametersChanged(int)));
	connect(((InteractiveColorLevelWidget *)interactiveOptionWidget)->saturationSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveColorLevelParametersChanged(int)));
	connect(((InteractiveColorLevelWidget *)interactiveOptionWidget)->contrastSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveColorLevelParametersChanged(int)));
	srcHSVMat.get()=Mat(srcMat->rows,srcMat->cols,CV_32FC3);
	ColorSpaceTransition::rgb2Hsv(srcMat.get(),srcHSVMat.get());
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::interactiveColorCorrectionActionTriggered()
{
	if(interactiveStatus&INTERACTIVE_COLOR_CORRECTION_SELECTED)
		return;
	if(interactiveHasProduceResult)
	{
		interactiveHasProduceResult=false;
		updateMat();
	}
	interactiveStatus=0;
	interactiveStatus|=INTERACTIVE_COLOR_CORRECTION_SELECTED;
	delete ImageLabel;
	ImageLabel=new OriginalImageLabel(ui.centralWidget);
	initImageLabel();
	interactiveOptionWidgetHasInit=true;
	delete interactiveOptionWidget;
	interactiveOptionWidget=new InteractiveColorCorrectionWidget(ui.centralWidget);
	interactiveOptionWidget->setGeometry(ImageLabel->x()+ImageLabel->width()+10,ImageLabel->y(),240,ImageLabel->height());
	interactiveOptionWidget->setVisible(true);
	interactiveColorCorrectionConnecting();
	updateDisplayImage();
	updateToolBar();
}
void ImageProcessSystem::interactiveColorCorrectionConnecting()
{
	InteractiveColorCorrectionWidget *widget=(InteractiveColorCorrectionWidget *)interactiveOptionWidget;
	connect(widget->redSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveColorCorrectionParametersChanged(int)));
	connect(widget->yellowSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveColorCorrectionParametersChanged(int)));
	connect(widget->brightnessSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveColorCorrectionParametersChanged(int)));
}
void ImageProcessSystem::interactiveLocalEnhencementConnecting()
{
	InteractiveLocalEnhencementWidget * widget=(InteractiveLocalEnhencementWidget *)interactiveOptionWidget;
	connect(widget->redEnhencementSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveLocalEnhencementParametersChanged(int)));
	connect(widget->isHold.get(),SIGNAL(clicked()),widget,SLOT(isHoldChanged()));
//	connect(widget->greenEnhencementSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveLocalEnhencementParametersChanged(int)));
//	connect(widget->blueEnhencementSlider.get(),SIGNAL(valueChanged(int)),this,SLOT(interactiveLocalEnhencementParametersChanged(int)));
}
void ImageProcessSystem::intercativeHighlightActionTriggered()
{
	if(interactiveStatus&INTERACTIVE_HIGHLIGHT_SELECTED)
		return;
	if(interactiveHasProduceResult)
	{
		interactiveHasProduceResult=false;
		updateMat();
		updateDisplayImage();
	}
	interactiveStatus=0;
	interactiveStatus|=INTERACTIVE_HIGHLIGHT_SELECTED;
	delete ImageLabel;
	ImageLabel=new HighLightLabel(ui.centralWidget);
	initImageLabel();
	ImageLabel->setParameters(&srcImage,ui.pixelValueLabel);
	connect(ImageLabel,SIGNAL(interactiveHighlightFinished()),this,SLOT(interactiveHighlightFinishSignalEmit()));
	interactiveOptionWidgetHasInit=true;
	delete interactiveOptionWidget;
	interactiveOptionWidget=new InteractiveHighlightWidget(ui.centralWidget);
	interactiveOptionWidget->setGeometry(ImageLabel->x()+ImageLabel->width()+10,ImageLabel->y(),240,ImageLabel->height());
	interactiveOptionWidget->setVisible(true);
	updateToolBar();
}
void ImageProcessSystem::interactiveHighlightFinishSignalEmit()
{
	memset(highlightMask.get().data,NOTHIGHLIGHT_PIXEL_VALUE,sizeof(uchar)*highlightMask->rows*highlightMask->cols);
	BasisOperation::qimage2OneChannelMat(((HighLightLabel *)ImageLabel)->paintMask,INTERACTIVE_PIXEL_VALUE,highlightMask.get(),HIGHLIGHT_PIXEL_VALUE);
	unsigned char mode=0;
	if(((InteractiveHighlightWidget *)interactiveOptionWidget)->possionMethodIsChecked())
	{
		//detect face is time-consuming
		face=Rect(1,1,srcMat->cols-1,srcMat->rows-1);
		mode=HIGHLIGHT_REMOVAL_POSSION_MATHOD;
	}
	else
	{
		faceDetectingCombined();
		srcMat.get().copyTo(resultMat.get());
		mode=HIGHLIGHT_REMOVAL_INPAINTING_MATHOD;
	}
	HighLightRemoval::removal(srcMat.get(),resultMat.get(),highlightMask.get(),face,mode);
	updateMat();
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::interactiveLocalEnhencementFinishSignalEmit()
{
	BasisOperation::qimage2OneChannelMat(((LocalEnhencementLabel *)ImageLabel)->paintMask,INTERACTIVE_PIXEL_VALUE,regionMask.get(),PIXEL_SELECTED_VALUE);
	blur(regionMask.get(),regionMask.get(),Size(featherRadius,featherRadius));
	double x=0.5,y;
	if(((InteractiveLocalEnhencementWidget *)interactiveOptionWidget)->dodgeRadioButton->isChecked())
	{
		y=0.45;
	}
	else
		y=0.55;
	srcMat.get().copyTo(resultMat.get());
	BasisOperation::localEnhencementUsingMappingMethod(resultMat.get(),&regionMask.get(),x,y);
	updateMat();
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::interactiveFaceActionTriggered()
{
	if(interactiveStatus&INTERACTIVE_FACE_SELECTED)
		return;
	if(interactiveHasProduceResult)
	{
		interactiveHasProduceResult=false;
		updateMat();
		updateDisplayImage();
	}
	interactiveStatus=0;
	interactiveStatus|=INTERACTIVE_FACE_SELECTED;
	delete ImageLabel;
	ImageLabel=new InteractiveFaceLabel(ui.centralWidget);
	initImageLabel();
	((InteractiveFaceLabel *)ImageLabel)->setParameters(&srcImage,ui.pixelValueLabel,&face);
	delete interactiveOptionWidget;
	interactiveOptionWidget=NULL;
	interactiveOptionWidgetHasInit=false;
	updateToolBar();
}
void ImageProcessSystem::interactiveLacalEnhencementActionTriggered()
{
	if(interactiveStatus&INTERACTIVE_LOCAL_ENHENCEMENT_SELECTED)
		return;
	if(interactiveHasProduceResult)
	{
		interactiveHasProduceResult=false;
		updateMat();
	}
	interactiveStatus=0;
	interactiveStatus|=INTERACTIVE_LOCAL_ENHENCEMENT_SELECTED;
	delete ImageLabel;
	ImageLabel=new LocalEnhencementLabel(ui.centralWidget);
	initImageLabel();
	((LocalEnhencementLabel *)(ImageLabel))->setParameters(&srcImage,ui.pixelValueLabel,&regionMask.get(),&srcMat.get(),tolerance,featherRadius);
	connect(ImageLabel,SIGNAL(interactiveLocalEnhencementFinished()),this,SLOT(interactiveLocalEnhencementFinishSignalEmit()));
	interactiveOptionWidgetHasInit=true;
	delete interactiveOptionWidget;
	interactiveOptionWidget=new InteractiveLocalEnhencementWidget(ui.centralWidget,(LocalEnhencementLabel *)ImageLabel);
	interactiveOptionWidget->setGeometry(ImageLabel->x()+ImageLabel->width()+10,ImageLabel->y(),240,ImageLabel->height());
	interactiveOptionWidget->setVisible(true);
	interactiveLocalEnhencementConnecting();
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::faceDetectingCombined()
{
	if(srcImage.isNull())
		return;
	if(!(processStatus&FACE_DETECTION_DONE))
	{
		memset(faceMask.get().data,NOTFACE_PIXEL_VALUE,srcImage.width()*srcImage.height()*sizeof(uchar));
		faceDetector::detectingFace(srcMat.get(),faceMask.get(),FACE_COLORMODEL|FACE_USINGOPENCV|FACE_USING_CLUSTER,face);
		dilate(faceMask.get(),faceMask.get(),Mat(),Point(-1,-1),5);
		erode(faceMask.get(),faceMask.get(),Mat(),Point(-1,-1),5);
		processStatus|=FACE_DETECTION_DONE;
	}
}
void ImageProcessSystem::insertItemIntoListWidget()
{
	fileNames.push_back(fileName);
	QListWidgetItem *item=new QListWidgetItem(QIcon(QPixmap::fromImage(srcImage)),NULL);
	ui.listWidget->addItem(item);
}
void ImageProcessSystem::clearImgaes()
{
	while(!images.empty())
		images.pop();
}
void ImageProcessSystem::initImageLabel()
{
	int w=srcImage.width(),h=srcImage.height();
	ImageLabel->setGeometry((ui.centralWidget->width()-w-ui.listWidget->width())/2+ui.listWidget->width(),(ui.centralWidget->height()-h)/2,w,h);
	ImageLabel->setVisible(true);
	ui.pixelValueLabel->setGeometry(ImageLabel->x()+(ImageLabel->width()-102)/2,ImageLabel->height()+ImageLabel->y()+5,102,12);
	ImageLabel->setParameters(&srcImage,ui.pixelValueLabel);
	ImageLabel->setMouseTracking(true);
	ImageLabel->displayImage(srcImage);
}
bool ImageProcessSystem::loadImage()
{
	if(!fileName.isEmpty())
	{
		QImage templeImage(fileName);
		if(templeImage.isNull())
		{
			QMessageBox::critical(this,"Error",fileName);
			return false;
		}
		clearImgaes();
		srcImage=templeImage;
		currentDisplayImageImproper=false;
#ifndef DEMO
		vector<QString>::iterator it =std::find(fileNames.begin(),fileNames.end(),fileName);
		if(it==fileNames.end())
		insertItemIntoListWidget();
#endif
		return true;
	}
	return false;
}
void ImageProcessSystem::resetStatus()
{
	processStatus=0;
	interactiveStatus=0;
}
void ImageProcessSystem::listWidgetClicked(QListWidgetItem *item)
{
	int r=ui.listWidget->row(item);
	fileName=fileNames[r];
	resetStatus();
	interactiveHasProduceResult=false;
	loadImage();
	updateToolBar();
	initMat();
	initImageLabel();
}
void ImageProcessSystem::openFile()
{
	fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"Images (*.bmp *.gif *.jpg *.jpeg *.png *.tiff)");
	if(!loadImage())
		return ;
	resetStatus();
	interactiveHasProduceResult=false;
	updateToolBar();
	initMat();
	delete ImageLabel;
	ImageLabel=new OriginalImageLabel(ui.centralWidget);
	initImageLabel();
}
void ImageProcessSystem::superPixelActionTriggered()
{
	//prepare
	faceDetectingCombined();
	resultImage=srcImage.copy(0,0,srcImage.width(),srcImage.height());
	int faceImgWidth=face.width,faceImgHeight=face.height*1.2;
	faceImgHeight=faceImgHeight>(srcImage.height()-face.y)?(srcImage.height()-face.y):faceImgHeight;
	//symmetry
	double *grayImageData=new double[faceImgWidth*faceImgHeight];
	unsigned char *srcImagePtr=(unsigned char *)srcImage.bits();
	double threeChannelSum;
	for(int i=face.y;i<face.y+faceImgHeight;++i)
		for(int j=face.x;j<face.x+faceImgWidth;++j)
		{
			threeChannelSum=srcImagePtr[4*(i*srcImage.width()+j)+2]+srcImagePtr[4*(i*srcImage.width()+j)+1]+srcImagePtr[4*(i*srcImage.width()+j)];
			grayImageData[(i-face.y)*faceImgWidth+j-face.x]=threeChannelSum/3;
		}
	Engine *ep=MatlabEngineHolder::getEngine();
	mxArray *imgDataMatlab=mxCreateDoubleMatrix(faceImgWidth,faceImgHeight,mxREAL);
	memcpy(mxGetPr(imgDataMatlab),grayImageData,faceImgWidth*faceImgHeight*sizeof(double));
	mxArray *xInMatlab,*yInMatlab;
	engPutVariable(ep,"img",imgDataMatlab);
	engEvalString(ep,"img=img';");
	engEvalString(ep,"cd bin/symmetry;");
	engEvalString(ep,"[X,Y]=symmetry(img,'mirror');");
	xInMatlab=engGetVariable(ep,"X");
	yInMatlab=engGetVariable(ep,"Y");
	double *xData=mxGetPr(xInMatlab);
	double *yData=mxGetPr(yInMatlab);
	int n=mxGetN(yInMatlab);
	if(n==0)
		return;
	// we assume the symmetry axis is vertical
	int symmetryAxisX;
	double sum=0;
	for(int i=0;i<n;++i)
		sum+=xData[i];
	symmetryAxisX=(int)(sum/n);
	faceImgWidth=2*(symmetryAxisX+1);
	//here faceImageWidth may exceeds the boundary,we treat it as error
	if(faceImgWidth>=srcImage.width()-face.x)
		return ;
	mxDestroyArray(imgDataMatlab);
	mxDestroyArray(xInMatlab);
	mxDestroyArray(yInMatlab);
	delete [] grayImageData;
	int *position=new int[srcMat->rows*srcMat->cols];
	memset(position,0,sizeof(int)*srcMat->rows*srcMat->cols);
	int pixelNumber=0;
	srcMat.get().copyTo(resultMat.get());
	for(int i=0;i<faceImgHeight;++i)
		for(int j=0;j<=symmetryAxisX;++j)
		{
			/*if(faceMask.at<uchar>(face.y+i,face.x+j)==FACE_PIXEL_VALUE)*/
			if(faceMask->at<uchar>(face.y+i,face.x+j)==FACE_PIXEL_VALUE&&faceMask->at<uchar>(face.y+i,faceImgWidth-1-j+face.x)==FACE_PIXEL_VALUE&&regionMask->at<uchar>(face.y+i,faceImgWidth-1-j+face.x)==PIXEL_NOT_SELECTED_VALUE)
			{
				resultMat->at<Vec3b>(face.y+i,face.x+j)=resultMat->at<Vec3b>(face.y+i,faceImgWidth-1-j+face.x);
			}
			else
				if(regionMask->at<uchar>(face.y+i,faceImgWidth-1-j+face.x)==PIXEL_SELECTED_VALUE)
				{
					regionMask->at<uchar>(face.y+i,faceImgWidth-1-j+face.x)=PIXEL_NOT_SELECTED_VALUE;
					regionMask->at<uchar>(face.y+i,face.x+j)=PIXEL_SELECTED_VALUE;
					position[(face.y+i)*srcMat->cols+face.x+j]=pixelNumber;
					pixelNumber++;
				}
		}
	//BasisOperation::poissonEditing(resultMat->get,resultMat,regionMask,position,pixelNumber,0,0.0,255.0);
	//BasisOperation::poissonEditing(resultMat,resultMat,regionMask,position,pixelNumber,1,0.0,255.0);
	//BasisOperation::poissonEditing(resultMat,resultMat,regionMask,position,pixelNumber,2,0.0,255.0);
	//super pixel
//	QImage faceImage=srcImage.copy(face.x,face.y,faceImgWidth,faceImgHeight);
//	QImage halfFaceImage=srcImage.copy(face.x,face.y,symmetryAxisX+1,faceImgHeight);
//	int *labels=new int[faceImgHeight*faceImgWidth];
//	int *halfLabels=new int[(symmetryAxisX+1)*faceImgHeight];
//	int numberLabels=0;
//	const int m_spcount=40;
//	const double m_compactness=10.0;
//	int gridWidth=(int)(sqrt((double)(halfFaceImage.width()*halfFaceImage.height())/m_spcount));
//	SLIC slic;
//	vector<double> kseedx(0),kseedy(0);
//	slic.PerformSLICO_ForGivenK((unsigned int *)halfFaceImage.bits(),halfFaceImage.width(),halfFaceImage.height(),halfLabels,numberLabels,m_spcount,m_compactness,kseedx,kseedy);
//	for(int i=0;i<faceImgHeight;++i)
//		memcpy(labels+i*faceImgWidth,halfLabels+i*(symmetryAxisX+1),sizeof(int)*(symmetryAxisX+1));
//	for(int i=0;i<faceImgHeight;++i)
//		for(int j=symmetryAxisX+1;j<faceImgWidth;++j)
//		{
//			labels[i*faceImgWidth+j]=2*numberLabels-halfLabels[i*(symmetryAxisX+1)+faceImgWidth-1-j];
//		}
//
//	//region merge
//	int *regionNeedAdjustFlag=new int[m_spcount];
//	if(!regionNeedAdjustFlag)
//		return ;
//	memset(regionNeedAdjustFlag,0,sizeof(int)*m_spcount);
//	srcMat.copyTo(resultMat);
//	int symmetryPointX,symmetryPointY;
//#ifdef  DISPLAY_SUPERPIXEL_AND_SYMMETRY
//	QPainter p(&resultImage);
//	p.setPen(QColor(0xff00ff00));
//	int needAdjustNumber=0;
//	const int initWidth=5,step=0;
//#endif
//	for(int i=0;i<numberLabels;++i)
//	{
//		symmetryPointX=faceImgWidth-1-((int)kseedx[i]);
//		symmetryPointY=(int)kseedy[i];
//		if(BasisOperation::regionNeedAdjust(resultMat,resultMat,(int)kseedx[i],(int)kseedy[i],symmetryPointX,symmetryPointY,gridWidth,face,faceMask,labels,faceImgWidth,faceImgHeight,0.1))
//		{
//			regionNeedAdjustFlag[labels[((int)kseedy[i])*faceImgWidth+((int)kseedx[i])]]=1;
//#ifdef  DISPLAY_SUPERPIXEL_AND_SYMMETRY
//			//p.drawEllipse(kseedx[i]+face.x,kseedy[i]+face.y,initWidth+step*needAdjustNumber,initWidth+step*needAdjustNumber);
//			//p.drawEllipse(face.x+symmetryPointX,face.y+symmetryPointY,initWidth+step*needAdjustNumber,initWidth+step*needAdjustNumber);
//			//needAdjustNumber++;
//#endif
//		}
//	}
//	int regionMergeLabel=-1,queueFrontI,queueFrontJ;
//	queue<QPoint> mergeQueue;
//	uchar *visited=new uchar[faceImgHeight*faceImgWidth];
//	if(!visited)
//		return ;
//	memset(visited,0,sizeof(uchar)*faceImgWidth*faceImgHeight);
//	for(int i=0;i<faceImgHeight;++i)
//		for(int j=0;j<=symmetryAxisX;++j)
//		{
//			if(!visited[i*faceImgWidth+j]&&regionNeedAdjustFlag[labels[i*faceImgWidth+j]])
//			{
//				regionMergeLabel=labels[i*faceImgWidth+j];
//				//for the purpose of find the combined area label
//				regionNeedAdjustFlag[regionMergeLabel]=2;
//				mergeQueue.push(QPoint(j,i));
//				visited[i*faceImgWidth+j]=1;
//				while(!mergeQueue.empty())
//				{
//					queueFrontI=mergeQueue.front().y();
//					queueFrontJ=mergeQueue.front().x();
//					mergeQueue.pop();
//					//up
//					if(queueFrontI>0&&!visited[((queueFrontI-1)*faceImgWidth+queueFrontJ)]&&regionNeedAdjustFlag[labels[(queueFrontI-1)*faceImgWidth+queueFrontJ]])
//					{
//						labels[(queueFrontI-1)*faceImgWidth+queueFrontJ]=regionMergeLabel;
//						labels[(queueFrontI-1)*faceImgWidth+faceImgWidth-1-queueFrontJ]=2*numberLabels-regionMergeLabel;
//						mergeQueue.push(QPoint(queueFrontJ,queueFrontI-1));
//						visited[((queueFrontI-1)*faceImgWidth+queueFrontJ)]=1;
//					}
//					//down
//					if((queueFrontI+1)<faceImgHeight&&!visited[(queueFrontI+1)*faceImgWidth+queueFrontJ]&&regionNeedAdjustFlag[labels[(queueFrontI+1)*faceImgWidth+queueFrontJ]])
//					{
//						labels[(queueFrontI+1)*faceImgWidth+queueFrontJ]=regionMergeLabel;
//						labels[(queueFrontI+1)*faceImgWidth+faceImgWidth-1-queueFrontJ]=2*numberLabels-regionMergeLabel;
//						mergeQueue.push(QPoint(queueFrontJ,queueFrontI+1));
//						visited[(queueFrontI+1)*faceImgWidth+queueFrontJ]=1;
//					}
//					//left
//					if(queueFrontJ>0&&!visited[queueFrontI*faceImgWidth+queueFrontJ-1]&&regionNeedAdjustFlag[labels[queueFrontI*faceImgWidth+queueFrontJ-1]])
//					{
//						labels[queueFrontI*faceImgWidth+queueFrontJ-1]=regionMergeLabel;
//						labels[queueFrontI*faceImgWidth+faceImgWidth-1-(queueFrontJ-1)]=2*numberLabels-regionMergeLabel;
//						mergeQueue.push(QPoint(queueFrontJ-1,queueFrontI));
//						visited[queueFrontI*faceImgWidth+queueFrontJ-1]=1;
//					}
//					//right
//					if((queueFrontJ+1)<=symmetryAxisX&&!visited[queueFrontI*faceImgWidth+queueFrontJ+1]&&regionNeedAdjustFlag[labels[queueFrontI*faceImgWidth+queueFrontJ+1]])
//					{
//						labels[queueFrontI*faceImgWidth+queueFrontJ+1]=regionMergeLabel;
//						labels[queueFrontI*faceImgWidth+faceImgWidth-1-(queueFrontJ+1)]=2*numberLabels-regionMergeLabel;
//						mergeQueue.push(QPoint(queueFrontJ+1,queueFrontI));
//						visited[queueFrontI*faceImgWidth+queueFrontJ+1]=1;
//					}
//				}
//			}
//		}
#ifdef DISPLAY_SUPERPIXEL_AND_SYMMETRY
		slic.DrawContoursAroundSegmentsTwoColors((unsigned int *)faceImage.bits(),labels,faceImgWidth,faceImgHeight);
		unsigned char * resultImagePtr=resultImage.bits();
		unsigned char *faceImagePtr=faceImage.bits();
		for(int i=0;i<faceImgHeight;++i)
		{
			memcpy(resultImagePtr+((face.y+i)*resultImage.width()+face.x)*4,faceImagePtr+4*i*faceImgWidth,4*faceImgWidth);
		}
#endif
	//delete [] visited;
	////color transfer and poisson editing
	//srcMat.copyTo(resultMat);
	////const int bins=100;
	////Mat labMat(srcMat.rows,srcMat.cols,CV_32FC3);
	////ColorSpaceTransition::rgb2Lab(srcMat,labMat);
	//int regionPixelNumber;
	//int *position=new int[srcMat.rows*srcMat.cols];
	//for(int i=0;i<numberLabels;++i)
	//{
	//	if(regionNeedAdjustFlag[i]==2)
	//	{
	//		Mat srcRegionMask=Mat::zeros(srcMat.rows,srcMat.cols,CV_8UC1),tarRegionMask=Mat::zeros(srcMat.rows,srcMat.cols,CV_8UC1);
	//		regionPixelNumber=0;
	//		memset(position,0,sizeof(int)*srcMat.rows*srcMat.cols);
	//		for(int j=0;j<faceImgHeight;++j)
	//			for(int k=0;k<faceImgWidth;++k)
	//			{
	//				if(labels[j*faceImgWidth+k]==i&&faceMask.at<uchar>(j+face.y,k+face.x)==FACE_PIXEL_VALUE&&faceMask.at<uchar>(j+face.y,faceImgWidth-1-k+face.x)==FACE_PIXEL_VALUE&&!BasisOperation::pixelIsBoundary(faceMask,k+face.x,j+face.y))
	//				{
	//				/*	srcRegionMask.at<uchar>(j+face.y,k+face.x)=PIXEL_SELECTED_VALUE;
	//					position[(j+face.y)*srcMat.cols+k+face.x]=regionPixelNumber;
	//					regionPixelNumber++;*/
	//					resultMat.at<Vec3b>(j+face.y,k+face.x)=srcMat.at<Vec3b>(j+face.y,faceImgWidth-1-k+face.x);
	//				}
	//			/*	if(labels[j*faceImgWidth+k]==(2*numberLabels-i)&&faceMask.at<uchar>(j+face.y,k+face.x)==FACE_PIXEL_VALUE&&!BasisOperation::pixelIsBoundary(faceMask,k+face.x,j+face.y))
	//					tarRegionMask.at<uchar>(j+face.y,k+face.x)=PIXEL_SELECTED_VALUE;*/
	//			}
	//	}
	//}
	////ColorSpaceTransition::lab2Rgb(labMat,resultMat);
	////free resource
	//delete [] position;
	//delete [] regionNeedAdjustFlag;
	//if(labels)
	//	delete [] labels;
	//if(halfLabels)
	//	delete [] halfLabels;
	//display result
#ifdef DISPLAY_SUPERPIXEL_AND_SYMMETRY
	ImageLabel->displayImage(resultImage);
#else
	updateMat();
	updateToolBar();
	updateDisplayImage();
#endif
}
void ImageProcessSystem::saveFile()
{
		QString saveFileName=QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath(),"Images (*.jpg *.gif *.bmp *.jpeg *.png *.tiff)");
		if(saveFileName.isEmpty())
			return;
		imwrite(saveFileName.toStdString(),srcMat.get());
}
void ImageProcessSystem::updateToolBar()
{
	if(currentDisplayImageImproper||interactiveStatus)
	{
		ui.actionColorCorrection->setEnabled(false);
		ui.actionHighLightDetection->setEnabled(false);
		ui.actionHighlightRemoval->setEnabled(false);
		ui.actionSave->setEnabled(false);
		ui.actionFace->setEnabled(false);
		ui.actionSuperPixel->setEnabled(false);
		ui.faceDetetingMenu->setEnabled(false);
		ui.sharpenAction->setEnabled(false);
		if(currentDisplayImageImproper)
		{
			ui.actionInteractiveColorCorrection->setEnabled(false);
			ui.actionInteractiveLocalEnhencement->setEnabled(false);
			ui.actionInteractiveHighlight->setEnabled(false);
			ui.actionInteractiveColorLevel->setEnabled(false);
			ui.actionInteractiveColorBalance->setEnabled(false);
			ui.actionSwitch->setEnabled(false);
			ui.actionInteractiveFace->setEnabled(false);
			if(images.empty())
				ui.actionCancel->setEnabled(false);
			else
				ui.actionCancel->setEnabled(true);
		}
		else
		{
			ui.actionSwitch->setEnabled(true);
			ui.actionCancel->setEnabled(false);
			if(interactiveStatus&INTERACTIVE_LOCAL_ENHENCEMENT_SELECTED)
			{
				ui.actionInteractiveLocalEnhencement->setIcon(QIcon(QString::fromUtf8(":/pictures/localenhencementselected.jpg")));
			}
			else
			{
				ui.actionInteractiveLocalEnhencement->setIcon(QIcon(QString::fromUtf8(":/pictures/localenhencementnotselected.jpg")));
			}
			if(interactiveStatus&INTERACTIVE_COLOR_CORRECTION_SELECTED)
			{
				ui.actionInteractiveColorCorrection->setIcon(QIcon(QString::fromUtf8(":/pictures/colorcorrectselected.jpg")));
			}
			else
			{
				ui.actionInteractiveColorCorrection->setIcon(QIcon(QString::fromUtf8(":/pictures/colorcorrectnotselected.jpg")));
			}
			if(interactiveStatus&INTERACTIVE_HIGHLIGHT_SELECTED)
			{
				ui.actionInteractiveHighlight->setIcon(QIcon(QString::fromUtf8(":/pictures/highlightselected.jpg")));
			}
			else
			{
				ui.actionInteractiveHighlight->setIcon(QIcon(QString::fromUtf8(":/pictures/highlightnotselected.jpg")));
			}
			if(interactiveStatus&INTERACTIVE_FACE_SELECTED)
			{
				ui.actionInteractiveFace->setIcon(QIcon(QString::fromUtf8(":/pictures/faceselected.jpg")));
			}
			else
			{
				ui.actionInteractiveFace->setIcon(QIcon(QString::fromUtf8(":/pictures/facenotselected.jpg")));

			}
			if(interactiveStatus&INTERACTIVE_COLOR_LEVEL_SELECTED)
			{
				ui.actionInteractiveColorLevel->setIcon(QIcon(QString::fromUtf8(":/pictures/colorlevelselected.jpg")));
			}
			else
			{
				ui.actionInteractiveColorLevel->setIcon(QIcon(QString::fromUtf8(":/pictures/colorlevelnotselected.jpg")));
			}
			if(interactiveStatus&INTERACTIVE_COLOR_BALANCE_SELECTED)
			{
				ui.actionInteractiveColorBalance->setIcon(QIcon(QString::fromUtf8(":/pictures/colorbalanceselected.jpg")));
			}
			else
			{
				ui.actionInteractiveColorBalance->setIcon(QIcon(QString::fromUtf8(":/pictures/colorbalancenotselected.jpg")));
			}
		}
	}
	else
	{
		ui.actionColorCorrection->setEnabled(true);
		ui.actionSuperPixel->setEnabled(true);
		ui.actionHighLightDetection->setEnabled(true);
		ui.actionHighlightRemoval->setEnabled(true);
		ui.actionSave->setEnabled(true);
		ui.actionFace->setEnabled(true);
		ui.faceDetetingMenu->setEnabled(true);
		ui.sharpenAction->setEnabled(true);
		ui.actionInteractiveLocalEnhencement->setEnabled(true);
		ui.actionInteractiveColorCorrection->setEnabled(true);
		ui.actionInteractiveHighlight->setEnabled(true);
		ui.actionInteractiveFace->setEnabled(true);
		ui.actionInteractiveColorLevel->setEnabled(true);
		ui.actionInteractiveColorBalance->setEnabled(true);
		if(images.empty())
			ui.actionCancel->setEnabled(false);
		else
			ui.actionCancel->setEnabled(true);
		if(interactiveOptionWidgetHasInit)
		{
			interactiveOptionWidget->hide();
		}
		ui.actionInteractiveLocalEnhencement->setIcon(QIcon(QString::fromUtf8(":/pictures/localenhencementnotselected.jpg")));
		ui.actionInteractiveColorCorrection->setIcon(QIcon(QString::fromUtf8(":/pictures/colorcorrectnotselected.jpg")));
		ui.actionInteractiveHighlight->setIcon(QIcon(QString::fromUtf8(":/pictures/highlightnotselected.jpg")));
		ui.actionInteractiveFace->setIcon(QIcon(QString::fromUtf8(":/pictures/facenotselected.jpg")));
		ui.actionInteractiveColorLevel->setIcon(QIcon(QString::fromUtf8(":/pictures/colorlevelnotselected.jpg")));
		ui.actionInteractiveColorBalance->setIcon(QIcon(QString::fromUtf8(":/pictures/colorbalancenotselected.jpg")));
		ui.actionSwitch->setEnabled(false);
	}
}
void ImageProcessSystem::interactiveSwitchActionTriggered()
{
	if(interactiveStatus&INTERACTIVE_FACE_SELECTED)
	{
		if(((InteractiveFaceLabel *)ImageLabel)->getFaceStatus())
		{
			memset(faceMask.get().data,NOTFACE_PIXEL_VALUE,srcImage.width()*srcImage.height()*sizeof(uchar));
			faceDetector::detectingFace(srcMat.get(),faceMask.get(),FACE_COLORMODEL,face);
			processStatus|=FACE_DETECTION_DONE;
		}
	}
	interactiveStatus=0;
	delete ImageLabel;
	ImageLabel=new OriginalImageLabel(ui.centralWidget);
	initImageLabel();
	if(interactiveHasProduceResult)
	{
		updateMat();
		interactiveHasProduceResult=false;
	}
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::interactiveLocalEnhencementParametersChanged(int value)
{
	InteractiveLocalEnhencementWidget *widget=(InteractiveLocalEnhencementWidget *)interactiveOptionWidget;
	widget->updateShowNumberLabel();
	double x=0.5,redY=widget->redEnhencementSlider->value()*0.01;//,greenY=widget->greenEnhencementSlider->value()*0.01,blueY=widget->blueEnhencementSlider->value()*0.01;
	srcMat.get().copyTo(resultMat.get());
	//BasisOperation::colorLevel(srcMat,resultMat,0,255,128-(widget->redEnhencementSlider->value()*0.01-0.5)*255);
	blur(regionMask.get(),regionMask.get(),Size(21,21));
	/*int w=srcMat.cols,h=srcMat.rows;
	double weight,redChannelValue,greenChannelValue,blueChannelValue;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			weight=regionMask.at<uchar>(j,i)/255.0;
			redChannelValue=weight*resultMat.at<Vec3b>(j,i)[2]+(1-weight)*srcMat.at<Vec3b>(j,i)[2];
			greenChannelValue=weight*resultMat.at<Vec3b>(j,i)[1]+(1-weight)*srcMat.at<Vec3b>(j,i)[1];
			blueChannelValue=weight*resultMat.at<Vec3b>(j,i)[0]+(1-weight)*srcMat.at<Vec3b>(j,i)[0];
			resultMat.at<Vec3b>(j,i)[2]=(unsigned char)redChannelValue;
			resultMat.at<Vec3b>(j,i)[1]=(unsigned char)greenChannelValue;
			resultMat.at<Vec3b>(j,i)[0]=(unsigned char)blueChannelValue;
		}*/
	BasisOperation::localEnhencementUsingMappingMethod(resultMat.get(),&regionMask.get(),x,redY);
	//BasisOperation::localEnhencementUsingMappingMethod(resultMat,&regionMask,x,redY,1);
	//BasisOperation::localEnhencementUsingMappingMethod(resultMat,&regionMask,x,redY,0);
	interactiveHasProduceResult=true;
	BasisOperation::mat2QImage(resultMat.get(),resultImage);
	ImageLabel->displayImage(resultImage);
}
void ImageProcessSystem::interactiveColorLevelParametersChanged(int value)
{
	InteractiveColorLevelWidget *widget=(InteractiveColorLevelWidget *)interactiveOptionWidget;
	widget->updateShowCurrentNumberLabel();
	srcMat.get().copyTo(resultMat.get());
	if(widget->saturationSlider->value()!=50||widget->lightnessSlider->value()!=50)
	{
		float diff;
		Mat hsvMat(srcMat->rows,srcMat->cols,CV_32FC3);
		//ColorSpaceTransition::rgb2Hsv(resultMat,hsvMat);
		srcHSVMat.get().copyTo(hsvMat);
		if(widget->saturationSlider->value()!=50)
		{
			diff=widget->saturationSlider->value()*0.01-0.5;
			BasisOperation::modifySaturationOrLightness(hsvMat,1,diff);
		}
		if(widget->lightnessSlider->value()!=50)
		{
			diff=widget->lightnessSlider->value()*0.01-0.5;
			BasisOperation::modifySaturationOrLightness(hsvMat,0,diff);
		}
		interactiveHasProduceResult=true;
		ColorSpaceTransition::hsv2Rgb(hsvMat,resultMat.get());
	}
	if(widget->redSlider->value()!=50||widget->contrastSlider->value()!=50)
	{
		interactiveHasProduceResult=true;
		unsigned char mid=(unsigned char)(widget->redSlider->value()*2.55);
		uchar diff=abs(widget->contrastSlider->value()-50);
		BasisOperation::colorLevel(resultMat.get(),resultMat.get(),0+diff,255-diff,mid);
	}
	BasisOperation::mat2QImage(resultMat.get(),resultImage);
	ImageLabel->displayImage(resultImage);
}
void ImageProcessSystem::interativeColorBalanceParametersChanged(int value)
{
	InteractiveColorBalanceWidget *widget=(InteractiveColorBalanceWidget *)interactiveOptionWidget;
	double red=widget->redSlider->value()*0.01;
	double green=widget->greenSlider->value()*0.01;
	double blue=widget->blueSlider->value()*0.01;
	widget->updateShowCurrentNumberLabel();
	BasisOperation::ColorBalance(srcMat.get(),resultMat.get(),red,green,blue);
	interactiveHasProduceResult=true;
	BasisOperation::mat2QImage(resultMat.get(),resultImage);
	ImageLabel->setParameters(&resultImage,ui.pixelValueLabel);
	ImageLabel->displayImage(resultImage);
}
void ImageProcessSystem::interactiveColorCorrectionParametersChanged(int value)
{
	InteractiveColorCorrectionWidget *widget=(InteractiveColorCorrectionWidget *)interactiveOptionWidget;
	double data1=widget->redSlider->value()*0.01;
	double data4=widget->yellowSlider->value()*0.01;
	double brightness=widget->brightnessSlider->value();
	blueMeans=(int)(brightness/(0.3*data1*data4+0.59*data4+0.11));
	greenMeans=(int)(data4*blueMeans);
	redMeans=(int)(data1*greenMeans);
	widget->updateShowCurrentNumberLabel();
	if(colorCorrection())
	{
		interactiveHasProduceResult=true;
		BasisOperation::mat2QImage(resultMat.get(),resultImage);
		ImageLabel->setParameters(&resultImage,ui.pixelValueLabel);
		ImageLabel->displayImage(resultImage);
	}
	else
	{
		QMessageBox::information(this,"Information","this picture is ok!");
	}
}
void ImageProcessSystem::cancelOperation()
{
	srcImage=images.top();
	currentDisplayImageImproper=false;
	BasisOperation::qimage2Mat(srcImage,srcMat.get());
	images.pop();
	resetStatus();
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::sharpEffect()
{
	BasisOperation::sharpEffect(srcMat.get(),resultMat.get());
	updateMat();
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::automaticHighlightRemoval()
{
	highlightDetection();
	srcMat.get().copyTo(resultMat.get());
	HighLightRemoval::removal(srcMat.get(),resultMat.get(),highlightMask.get(),face,HIGHLIGHT_REMOVAL_POSSION_MATHOD);
	updateMat();
	updateToolBar();
#ifdef DEBUG
	imshow("result",resultMat.get());
#else
	updateDisplayImage();
#endif
}
void ImageProcessSystem::automaticHighlightDetecting()
{
	highlightDetection();
	images.push(srcImage);
	currentDisplayImageImproper=true;
#ifdef DEBUG
	imshow("highlight",highlightMask.get());
#else
	Mat highlightMaskThreeChannel;
	cvtColor(highlightMask.get(),highlightMaskThreeChannel,CV_GRAY2BGR);
	QImage highlightMaskImage(highlightMask->cols,highlightMask->rows,QImage::Format_RGB32);
	BasisOperation::mat2QImage(highlightMaskThreeChannel,highlightMaskImage);
	ImageLabel->displayImage(highlightMaskImage);
#endif
	updateToolBar();
}
void ImageProcessSystem::highlightDetection()
{
	if(!(processStatus&HIGHLIGHT_DETECTION_DONE))
	{
		faceDetectingCombined();
		memset(highlightMask.get().data,NOTHIGHLIGHT_PIXEL_VALUE,highlightMask->cols*highlightMask->rows*sizeof(uchar));
		HighLightDetection::highlightDetection(highlightMask.get(),srcMat.get(),faceMask.get(),HIGHLIGHT_VALUE_SATURATION_METHOD,face);
		//dilate(highlightMask,highlightMask,Mat(),Point(-1,-1),10);
		//erode(highlightMask,highlightMask,Mat(),Point(-1,-1),10);
		processStatus|=HIGHLIGHT_DETECTION_DONE;
	}
}
//when loading a new image
void ImageProcessSystem::initMat()
{
	faceMask.get()=Mat::zeros(srcImage.height(),srcImage.width(),CV_8UC1);
	highlightMask.get()=Mat::zeros(srcImage.height(),srcImage.width(),CV_8UC1);
	regionMask.get()=Mat::zeros(srcImage.height(),srcImage.width(),CV_8UC1);
	srcMat.get()=Mat(srcImage.height(),srcImage.width(),CV_8UC3);
	resultMat.get()=Mat(srcImage.height(),srcImage.width(),CV_8UC3);
	resultImage=QImage(srcImage.width(),srcImage.height(),QImage::Format_RGB32);
	BasisOperation::qimage2Mat(srcImage,srcMat.get());
	face=Rect(0,0,srcMat->cols,srcMat->rows);
}
void ImageProcessSystem::updateDisplayImage()
{
	ImageLabel->displayImage(srcImage);
}
//when we got a new result image
void ImageProcessSystem::updateMat()
{
	images.push(srcImage);
	resultMat.get().copyTo(srcMat.get());
	processStatus=0;
	BasisOperation::mat2QImage(srcMat.get(),srcImage);
}
bool ImageProcessSystem::colorCorrection()
{
	faceDetectingCombined();
	if(!BasisOperation::faceNeedColorCorrection(srcMat.get(),faceMask.get(),face))
	{
		QMessageBox::information(this,"Information","this picture is ok!");
		return false;
	}
	ColorCorrection b(srcMat.get(),faceMask.get(),resultMat.get(),blueMeans,0),g(srcMat.get(),faceMask.get(),resultMat.get(),greenMeans,1),r(srcMat.get(),faceMask.get(),resultMat.get(),redMeans,2);
	b.automaticColorCorrection();
	g.automaticColorCorrection();
	r.automaticColorCorrection();
	return true;
}
void ImageProcessSystem::automaticLocalEnhencement()
{
	BasisOperation::colorLevel(srcMat.get(),resultMat.get(),0,255,2);
	updateMat();
	updateToolBar();
	updateDisplayImage();
}
void ImageProcessSystem::automaticColorCorrection()
{
	if(colorCorrection())
	{
		updateMat();
		updateToolBar();
#ifdef DEBUG
		imshow("result",resultMat.get());
#else
		updateDisplayImage();
#endif
	}
}
#endif