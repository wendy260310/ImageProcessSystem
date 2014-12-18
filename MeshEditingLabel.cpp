#include "header.h"
#include "BasisOperation.h"
#include "triangle/triangle.h"
#include "MeshEditingLabel.h"
InteractiveMeshEditingLabel::InteractiveMeshEditingLabel(struct triangulateio &_io,struct triangulateio &_symmIO,QWidget *parent/* =0 */):OriginalImageLabel(parent),io(_io),symmIO(_symmIO),startPos(-1,-1),selectPointThreshold(5)
{
	drawingImage=*srcImage;
	displayTriangle();
	pointSelected=false;
	isMoving=false;
	currentSelectedPointIndex=-1;
}
void InteractiveMeshEditingLabel::mouseMoveEvent(QMouseEvent *ev)
{
	if(isMoving)
	{
		symmIO.pointlist[2*currentSelectedPointIndex]=ev->x();
		symmIO.pointlist[2*currentSelectedPointIndex+1]=ev-y();
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
	BasisOperation::renderingTriangle(io,drawingImage);
	BasisOperation::renderingTriangle(symmIO,drawingImage);
	if(currentSelectedPointIndex!=-1)
	{

	}
	displayImage(drawingImage);
}
void InteractiveMeshEditingLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	if(ev->pos()==startPos)
	{
		if(pointSelected)
		{
			startPos=ev->pos();
		}
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