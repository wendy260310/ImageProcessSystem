#ifndef HIGHLIGHTLABEL_H
#define HIGHLIGHTLABEL_H
#ifndef EXPORT_DLL
#include "InteractiveImageLabel.h"
class HighLightLabel:public InteractiveImageLabel
{
	Q_OBJECT
public:
	HighLightLabel(QWidget *parent=0);
	~HighLightLabel(){};
signals:
	void interactiveHighlightFinished();
protected:
	void mouseReleaseEvent(QMouseEvent *ev);
};
#endif
#endif