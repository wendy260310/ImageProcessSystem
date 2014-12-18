#ifndef MESH_EDITING_LABEL
#define MESH_EDITING_LABEL
#include "OriginalImageLabel.h"
struct triangulateio;
class InteractiveMeshEditingLabel:public OriginalImageLabel
{
public:
	InteractiveMeshEditingLabel(struct triangulateio &_io,struct triangulateio &_symmIO,QWidget *parent=0);
protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
private:
	void displayTriangle();
	void pointSelect(QPoint &p);
	struct triangulateio &io,symmIO;
	QImage drawingImage;
	int currentSelectedPointIndex;
	QPoint startPos;
	const int selectPointThreshold;
	bool pointSelected;
	bool isMoving;
};
#endif