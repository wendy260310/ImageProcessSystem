#include "InteractiveImageLabel.h"
#include "parameters.h"
InteractiveImageLabel::InteractiveImageLabel(QWidget *parent):OriginalImageLabel(parent),penWidth(30)
{
	isDrawing=false;
}
void InteractiveImageLabel::resetPaintMask()
{
	paintMask.fill(QColor::fromRgba(0));
}
void InteractiveImageLabel::setParameters(QImage *_srcImage,QLabel *_displayRGBInformationLabel)
{
	OriginalImageLabel::setParameters(_srcImage,_displayRGBInformationLabel);
	paintMask=QImage(srcImage->width(),srcImage->height(),QImage::Format_ARGB32);
}
void InteractiveImageLabel::drawPaintMask(const QPoint &position)
{
	QPainter p(&paintMask);
	p.setPen(QPen(QBrush(QColor::fromRgba(INTERACTIVE_PIXEL_VALUE)),penWidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	p.drawLine(lastpos,position);
	lastpos=position;
}
void InteractiveImageLabel::mousePressEvent(QMouseEvent *ev)
{
	if(ev->button()==Qt::LeftButton)
	{
		resetPaintMask();
		isDrawing=true;
		lastpos=ev->pos();
		startpos=ev->pos();
	}
}
void InteractiveImageLabel::mouseMoveEvent(QMouseEvent *ev)
{
	OriginalImageLabel::mouseMoveEvent(ev);
	if(isDrawing)
	{
		drawPaintMask(ev->pos());
		displayPaintMask();
	}
}
void InteractiveImageLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	if(ev->button()==Qt::LeftButton)
	{
		if(isDrawing)
		{
			isDrawing=false;
		}
	}
}
void InteractiveImageLabel::displayPaintMask()
{

	QImage temp=*srcImage;
	QPainter painter(&temp);
	painter.setCompositionMode(QPainter::CompositionMode_Multiply);
	painter.drawImage(0,0,paintMask);
	painter.end();
	displayImage(temp);
}