#include "HighlightInteractiveDialog.h"
HighlightInteractiveDialog::HighlightInteractiveDialog()
{
	ui.setupUi(this);
	connect(ui.cancelButton,SIGNAL(clicked()),this,SLOT(resetMask()));
	connect(ui.threshSlider,SIGNAL(valueChanged(int)),this,SLOT(highlightParametersChanged(int)));
	connect(ui.okButton,SIGNAL(clicked()),this,SLOT(highlightRemoval()));
	connect(ui.BrushRadioButton,SIGNAL(clicked()),this,SLOT(updateGroupBox()));
	connect(ui.thresholdRadioButton,SIGNAL(clicked()),this,SLOT(updateGroupBox()));
	usingBrush=false;
	resultImage=NULL;
};
void HighlightInteractiveDialog::updateGroupBox()
{
	if(ui.BrushRadioButton->isChecked())
	{
		resetMask();
		usingBrush=true;
		ui.threshSlider->setEnabled(false);
		ui.label->enableBrush(true);
		return;
	}
	if(ui.thresholdRadioButton->isChecked())
	{
		resetMask();
		usingBrush=false;
		ui.threshSlider->setEnabled(true);
		return;
	}
}
void HighlightInteractiveDialog::setVariable(QImage *_srcImg,Mat *_srcMat,Mat *_faceMask,Rect _face,Mat *_highlightMat,Mat *_resultMat)
{
	srcImg=_srcImg;
	srcMat=_srcMat;
	faceMask=_faceMask;
	face=_face;
	highlightMask=_highlightMat;
	resultMat=_resultMat;
	ui.label->setGeometry((this->width()-srcImg->width())>>1,(this->height()-srcImg->height())>>1,srcImg->width(),srcImg->height());
	ui.layoutWidget->setGeometry((this->width()-ui.layoutWidget->width())>>1,ui.label->y()+ui.label->height()+5,ui.layoutWidget->width(),ui.layoutWidget->height());
	ui.label->setImage(srcImg);
	ui.label->displayImage();
}
void HighlightInteractiveDialog::resetMask()
{
	ui.label->resetMask();
	ui.label->displayImage();
	memset(highlightMask->data,NOTHIGHLIGHT_PIXEL_VALUE,sizeof(uchar)*srcImg->width()*srcImg->height());
}
void HighlightInteractiveDialog::highlightQImage2Mat()
{
	QImage &t=ui.label->getMask();
	int w=t.width(),h=t.height();
	const unsigned int *ptr=(unsigned int *)t.constBits();
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			if(*ptr==HIGHLIGHT_INTERACTIVE_PIXEL_VALUE)
				highlightMask->at<uchar>(j,i)=HIGHLIGHT_PIXEL_VALUE;
			++ptr;
		}
}
void HighlightInteractiveDialog::highlightRemoval()
{
	if(usingBrush)
		highlightQImage2Mat();
	HighLightRemoval::removal(*srcMat,*resultMat,*highlightMask,face,HIGHLIGHT_REMOVAL_POSSION_MATHOD);
	delete resultImage;
	resultImage=new QImage(srcMat->cols,srcMat->rows,QImage::Format_RGB32);
	BasisOperation::mat2QImage(*resultMat,*resultImage);
	ui.label->setImage(resultImage);
	ui.label->displayImage();
	srcImg=resultImage;
}
void HighlightInteractiveDialog::closeEvent(QCloseEvent *ev)
{
	delete resultImage;
	resultImage=NULL;
	ev->accept();
}
HighlightInteractiveDialog::~HighlightInteractiveDialog(void)
{
	delete resultImage;
	resultImage=NULL;
}
void HighlightInteractiveDialog::highlightParametersChanged(int value)
{
	double sRatio=value*0.005;
	ui.thresholdLabel->setText(QString::number(sRatio));
	memset(highlightMask->data,NOTHIGHLIGHT_PIXEL_VALUE,sizeof(uchar)*srcImg->width()*srcImg->height());
	HighLightDetection::highlightDetection(*highlightMask,*srcMat,*faceMask,HIGHLIGHT_VALUE_SATURATION_METHOD,face,sRatio);
	dilate(*highlightMask,*highlightMask,Mat(),Point(-1,-1),5);
	erode(*highlightMask,*highlightMask,Mat(),Point(-1,-1),5);
	ui.label->setMask(*highlightMask);
}
QImage & HighlightInteractiveDialog::getMask()
{
	return ui.label->getMask();
}