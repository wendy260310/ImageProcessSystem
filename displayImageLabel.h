#ifndef DISPLAYIMAGELABEL_H
#define DISPLAYIMAGELABEL_H
#include "e:\qt\4.8.2\src\gui\widgets\qlabel.h"
#include "header.h"
class displayImageLabel :
	public QLabel
{
public:
	void displayImage(QImage &image);
	void setDisplayPixelValueLabel(QLabel *l){displayPixelValueLabel=l;};
	void setImage(QImage *m){img=m;}
	displayImageLabel(QWidget *parent=0);
	displayImageLabel(void);
	~displayImageLabel(void);
protected:
	void enterEvent(QEvent *ev);
	void leaveEvent(QEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
private:
	QLabel *displayPixelValueLabel;
	QImage *img;
};
#endif
