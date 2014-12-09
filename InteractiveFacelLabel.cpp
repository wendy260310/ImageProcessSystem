#include "InteractiveFaceLabel.h"
InteractiveFaceLabel::InteractiveFaceLabel(QWidget *parent/* =0 */):OriginalImageLabel(parent)
{
	face=NULL;
	isDrawing=false;
	hasSpecifyFace=false;
}
void InteractiveFaceLabel::setParameters(QImage *_srcImage,QLabel *_displayRGBInformationLabel,Rect *_face)
{
	OriginalImageLabel::setParameters(_srcImage,_displayRGBInformationLabel);
	face=_face;
}
void InteractiveFaceLabel::mousePressEvent(QMouseEvent *ev)
{
	if(ev->button()==Qt::LeftButton)
	{
		startPoint=ev->pos();
		isDrawing=true;
	}
}
void InteractiveFaceLabel::mouseMoveEvent(QMouseEvent *ev)
{
	OriginalImageLabel::mouseMoveEvent(ev);
	if(isDrawing)
	{
		QImage temp=*srcImage;
		QPainter p(&temp);
		p.drawRect(QRect(startPoint,ev->pos()));
		p.end();
		displayImage(temp);
	}
}
void InteractiveFaceLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	if(ev->button()==Qt::LeftButton)
	{
		if(isDrawing)
		{
			isDrawing=false;
			face->x=startPoint.x();
			face->y=startPoint.y();
			face->width=ev->x()-face->x;
			face->height=ev->y()-face->y;
			hasSpecifyFace=true;
		}
	}
}