#ifndef INTERACTIVE_FACE_LABEL_H
#define INTERACTIVE_FACE_LABEL_H
#include "OriginalImageLabel.h"
#include "header.h"
class InteractiveFaceLabel:public OriginalImageLabel
{
public:
	InteractiveFaceLabel(QWidget *parent=0);
	void setParameters(QImage *_srcImage,QLabel *_displayRGBInformationLabel,Rect *_face);
	bool getFaceStatus(){return hasSpecifyFace;}
protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
private:
	Rect *face;
	bool hasSpecifyFace;
	QPoint startPoint;
	bool isDrawing;
};
#endif