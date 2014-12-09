#ifndef ORIGINAL_IMAGE_LABEL_H
#define ORIGINAL_IMAGE_LABEL_H
#include "header.h"
class OriginalImageLabel:public QLabel
{
public:
	OriginalImageLabel(QWidget *parent=0);
	virtual ~OriginalImageLabel(){};
	void virtual setParameters(QImage *_srcImage,QLabel *_displayRGBInformationLabel);
	void displayImage();
	void displayImage(QImage &img);
protected:
	void enterEvent(QEvent *ev);
	void leaveEvent(QEvent *ev);
	void virtual mouseMoveEvent(QMouseEvent *ev);
	QImage *srcImage;
	QLabel *displayRGBInformationLabel;
};
#endif