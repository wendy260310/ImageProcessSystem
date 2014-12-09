#ifndef LOCAL_ENHENCEMENT_LABEL_H
#define LOCAL_ENHENCEMENT_LABEL_H
#include "InteractiveImageLabel.h"
#include "header.h"
class LocalEnhencementLabel:public InteractiveImageLabel
{
	Q_OBJECT
public:
	LocalEnhencementLabel(QWidget *parent=0);
	void setParameters(QImage *_srcImage,QLabel *_displayRGBInformationLabel,Mat *_regionMask,Mat *_srcMat,int _tolerance,int _featureRadius);
	void setRegionIsHolding(bool status){regionIsHolding=status;};
signals:
	void interactiveLocalEnhencementFinished();
protected:
	void mouseReleaseEvent(QMouseEvent *ev);
	void resetRegionMask();
	void paintCounters();
	Mat *regionMask;
	Mat *srcMat;
	Rect region;
	int tolerance,featherRadius;
	bool regionIsHolding;
};
#endif