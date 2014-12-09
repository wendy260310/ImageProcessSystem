#include "displayImageLabel.h"
displayImageLabel::displayImageLabel(void)
{
}
displayImageLabel::displayImageLabel(QWidget *parent):QLabel(parent)
{
	setMouseTracking(false);
	displayPixelValueLabel=NULL;
}
displayImageLabel::~displayImageLabel(void)
{
}
void displayImageLabel::displayImage(QImage &image)
{
	clear();
	setPixmap(QPixmap::fromImage(image));
	update();
}
void displayImageLabel::enterEvent(QEvent *ev)
{
	if(displayPixelValueLabel)
		displayPixelValueLabel->setVisible(true);
}
void displayImageLabel::leaveEvent(QEvent *ev)
{
	if(displayPixelValueLabel)
		displayPixelValueLabel->setVisible(false);
}
void displayImageLabel::mouseMoveEvent(QMouseEvent *ev)
{
	int x=ev->x();
	int y=ev->y();
	const unsigned char *imgPtr=img->constBits();
	QString s;
	s.reserve(20);
	s+="R:";
	s+=QString(QString::number(imgPtr[4*(y*img->width()+x)+2]));
	s+=",G:";
	s+=QString(QString::number(imgPtr[4*(y*img->width()+x)+1]));
	s+=",B:";
	s+=QString(QString::number(imgPtr[4*(y*img->width()+x)]));
	displayPixelValueLabel->setText(s);
}