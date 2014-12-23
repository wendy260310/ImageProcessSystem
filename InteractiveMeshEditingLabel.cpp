#include "header.h"
#include "BasisOperation.h"
#include "triangle/triangle.h"
#include "InteractiveMeshEditingLabel.h"
InteractiveMeshEditingLabel::InteractiveMeshEditingLabel(struct triangulateio &_io,struct triangulateio &_symmIO,QWidget *parent/* =0 */):OriginalImageLabel(parent),io(_io),symmIO(_symmIO),startPos(-1,-1),selectPointThreshold(5)
{
	pointSelected=false;
	isMoving=false;
	currentSelectedPointIndex=-1;
}
void InteractiveMeshEditingLabel::mouseMoveEvent(QMouseEvent *ev)
{
	OriginalImageLabel::mouseMoveEvent(ev);
	if(isMoving&&pointSelected)
	{
		symmIO.pointlist[2*currentSelectedPointIndex]=ev->x();
		symmIO.pointlist[2*currentSelectedPointIndex+1]=ev->y();
		displayTriangle();
	}
}
void InteractiveMeshEditingLabel::mousePressEvent(QMouseEvent *ev)
{
	if(!pointSelected)
	{
		startPos=ev->pos();
	}
	isMoving=true;
}
void InteractiveMeshEditingLabel::displayTriangle()
{
	drawingImage=srcImage->copy(0,0,srcImage->width(),srcImage->height());
	BasisOperation::renderingTriangle(io,drawingImage);
	BasisOperation::renderingTriangle(symmIO,drawingImage);
	if(currentSelectedPointIndex!=-1)
	{
		QPainter p(&drawingImage);
		p.setPen(QPen(QBrush(QColor::fromRgba(0xff00ff00)),5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
		p.drawPoint(symmIO.pointlist[2*currentSelectedPointIndex],symmIO.pointlist[2*currentSelectedPointIndex+1]);
		p.end();
	}
	displayImage(drawingImage);
	//drawingImage.save("hello.jpg");
}
void InteractiveMeshEditingLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	if(ev->pos()==startPos)
	{
		if(pointSelected)
		{
			startPos=ev->pos();
		}
		pointSelected=true;
		pointSelect(startPos);
		displayTriangle();
	}
	isMoving=false;
}
void InteractiveMeshEditingLabel::pointSelect(QPoint &p)
{
	for(int i=0;i<symmIO.numberofpoints;++i)
	{
		if(((p.x()-symmIO.pointlist[2*i])*(p.x()-symmIO.pointlist[2*i])+(p.y()-symmIO.pointlist[2*i+1])*(p.y()-symmIO.pointlist[2*i+1]))<selectPointThreshold*selectPointThreshold)
		{
			currentSelectedPointIndex=i;
			return;
		}
	}
}