#ifndef INTERACTIVE_TRIANGLE_LABEL_H
#define INTERACTIVE_TRIANGLE_LABEL_H
#include "OriginalImageLabel.h"
class InteractiveTriangleLabel:public OriginalImageLabel
{
public:
	InteractiveTriangleLabel(vector<double> &_pointX,vector<double> &_pointY,QWidget *parent=0);
	void initDrawingImage(){drawingImage=*srcImage;p.begin(&drawingImage);p.setPen(QPen(QBrush(QColor::fromRgba(0xff00ff00)),5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));}
protected:
	void mouseReleaseEvent(QMouseEvent *ev);
private:
	vector<double> &pointX,&pointY;
	QImage drawingImage;
	QPainter p;
};
#endif