#include "LocalEnhencementLabel.h"
#include "parameters.h"
#include "BasisOperation.h"
void LocalEnhencementLabel::setParameters(QImage *_srcImage,QLabel *_displayRGBInformationLabel,Mat *_regionMask,Mat *_srcMat,int _tolerance,int _featureRadius)
{
	InteractiveImageLabel::setParameters(_srcImage,_displayRGBInformationLabel);
	regionMask=_regionMask;
	srcMat=_srcMat;
	tolerance=_tolerance;
	featherRadius=_featureRadius;
}
LocalEnhencementLabel::LocalEnhencementLabel(QWidget *parent):InteractiveImageLabel(parent)
{
	regionMask=NULL;
	regionIsHolding=false;
}
void LocalEnhencementLabel::resetRegionMask()
{
	if(!regionIsHolding)
		memset(regionMask->data,PIXEL_NOT_SELECTED_VALUE,sizeof(uchar)*regionMask->rows*regionMask->cols);
}
void LocalEnhencementLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	InteractiveImageLabel::mouseReleaseEvent(ev);
	if(ev->button()==Qt::LeftButton&&startpos==ev->pos())
	{
		resetRegionMask();
		BasisOperation::regionExtraction(srcMat,regionMask,tolerance,region,ev->x(),ev->y());
		paintCounters();
		//Mat temp=Mat::zeros(regionMask->rows,regionMask->cols,CV_8UC1);
		//blur(*regionMask,temp,Size(featherRadius,featherRadius));
		//for(int i=0;i<regionMask->cols;++i)
		//	for(int j=0;j<regionMask->rows;++j)
		//	{
		//		if(regionMask->at<uchar>(j,i)==PIXEL_SELECTED_VALUE)
		//			regionMask->at<uchar>(j,i)=temp.at<uchar>(j,i);
		//	}
	}
	else
	{
		if(ev->button()==Qt::LeftButton)
		{
			resetRegionMask();
			emit interactiveLocalEnhencementFinished();
		}
	}
}
void LocalEnhencementLabel::paintCounters()
{
	int x=region.x,y=region.y,w=region.width,h=region.height;
	QImage temp=*srcImage;
	QPainter p(&temp);
	for(int i=x;i<x+w;++i)
		for(int j=y;j<h+y;++j)
		{
			if(BasisOperation::pixelIsBoundary(*regionMask,i,j))
			{
				p.drawPoint(i,j);
			}
		}
		p.end();
		displayImage(temp);
}