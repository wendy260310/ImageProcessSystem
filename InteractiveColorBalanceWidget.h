#ifndef EXPORT_DLL
#ifndef INTERACTIVE_COLOR_BALANCE_WIDGET_H
#define INTERACTIVE_COLOR_BALANCE_WIDGET_H
#include "header.h"
class InteractiveColorBalanceWidget:public QWidget
{
public:
	InteractiveColorBalanceWidget(QWidget *parent);
	shared_ptr<QSlider> redSlider,blueSlider,greenSlider;
	shared_ptr<QLabel> redMinLabel,redMaxLabel,blueMinLabel,blueMaxLabel,greenMinLabel,greenMaxLabel;
	shared_ptr<QLabel> redIllustrationLabel,greenIllustrationLabel,blueIllustrationLabel;
	shared_ptr<QLabel> redShowCurrentNumberLabel,greenShowCurrentNumberLabel,blueShowCurrentNumberLabel;
	void updateShowCurrentNumberLabel();
protected:
	void resizeEvent(QResizeEvent *ev);
private:
	void initWidget();
};
#endif
#endif