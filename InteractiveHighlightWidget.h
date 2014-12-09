#ifndef INTERACTIVE_HIGHLIGHT_WIDGET_H
#define INTERACTIVE_HIGHLIGHT_WIDGET_H
#include "header.h"
class InteractiveHighlightWidget:public QWidget
{
public:
	InteractiveHighlightWidget(QWidget *parent=0);
	bool possionMethodIsChecked(){ return possionMethodRadioButton->isChecked();}
protected:
	void resizeEvent(QResizeEvent *ev);
	shared_ptr<QRadioButton> possionMethodRadioButton,inpaintingMethodRadioButton;
private:
	void initWidget();
};
#endif