#include "OriginalImageLabel.h"
OriginalImageLabel::OriginalImageLabel(QWidget *parent):QLabel(parent)
{
	srcImage=NULL;
	displayRGBInformationLabel=NULL;
}
void OriginalImageLabel::setParameters(QImage *_srcImage,QLabel *_displayRGBInformationLabel)
{
	srcImage=_srcImage;
	displayRGBInformationLabel=_displayRGBInformationLabel;
}
void OriginalImageLabel::displayImage()
{
	displayImage(*srcImage);
}
void OriginalImageLabel::displayImage(QImage &img)
{
	clear();
	setPixmap(QPixmap::fromImage(img));
	update();
}
void OriginalImageLabel::enterEvent(QEvent *ev)
{
	if(displayRGBInformationLabel)
		displayRGBInformationLabel->setVisible(true);
}
void OriginalImageLabel::leaveEvent(QEvent *ev)
{
	if(displayRGBInformationLabel)
		displayRGBInformationLabel->setVisible(false);
}
void OriginalImageLabel::mouseMoveEvent(QMouseEvent *ev)
{
	if(displayRGBInformationLabel==NULL)
		return;
	int x=ev->x();
	int y=ev->y();
	if(x>=srcImage->width()||y>=srcImage->height())
		return;
	const unsigned char *imgPtr=srcImage->constBits();
	QString s;
	s.reserve(20);
	s+="R:";
	s+=QString(QString::number(imgPtr[4*(y*srcImage->width()+x)+2]));
	s+=",G:";
	s+=QString(QString::number(imgPtr[4*(y*srcImage->width()+x)+1]));
	s+=",B:";
	s+=QString(QString::number(imgPtr[4*(y*srcImage->width()+x)]));
	displayRGBInformationLabel->setText(s);
}