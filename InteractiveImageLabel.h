#ifndef INTERACTIVE_IMAGE_LABEL_H
#define INTERACTIVE_IMAGE_LABEL_H
#include "OriginalImageLabel.h"
class InteractiveImageLabel:public OriginalImageLabel
{
public:
	InteractiveImageLabel(QWidget *parent);
	void virtual setParameters(QImage *_srcImage,QLabel *_displayRGBInformationLabel);
	QImage paintMask;
	virtual ~InteractiveImageLabel(){};
protected:
	void virtual mousePressEvent(QMouseEvent *ev);
	void virtual mouseMoveEvent(QMouseEvent *ev);
	void virtual mouseReleaseEvent(QMouseEvent *ev);
	void resetPaintMask();
	void drawPaintMask(const QPoint &position);
	void displayPaintMask();
	bool isDrawing;
	QPoint lastpos;
	QPoint startpos;
	const int penWidth;
};
#endif
