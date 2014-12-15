#include "InteractiveTriangleLabel.h"
InteractiveTriangleLabel::InteractiveTriangleLabel(vector<double> &_pointX,vector<double> &_pointY,QWidget *parent/* =0 */):OriginalImageLabel(parent),pointX(_pointX),pointY(_pointY)
{
	pointX.clear();
	pointY.clear();
}
void InteractiveTriangleLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	pointX.push_back(ev->x());
	pointY.push_back(ev->y());
	//QPainter p(&drawingImage);
	p.drawPoint(ev->pos());
	//p.end();
	displayImage(drawingImage);
}