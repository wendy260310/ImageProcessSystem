#ifndef INTERACTIVE_LOCAL_ENHENCEMENT_H
#define INTERACTIVE_LOCAL_ENHENCEMENT_H
#include "header.h"
class LocalEnhencementLabel;
class InteractiveLocalEnhencementWidget:public QWidget
{
	Q_OBJECT
public:
	InteractiveLocalEnhencementWidget(QWidget *parent,LocalEnhencementLabel *_label);
	shared_ptr<QSlider> redEnhencementSlider;//,greenEnhencementSlider,blueEnhencementSlider;
	shared_ptr<QLabel> redEnhencementMinLabel,redEnhencementMaxLabel,redEnhencementShowNumberLabel,redIllustrationLabel;
	//shared_ptr<QLabel> greenEnhencementMinLabel,greenEnhencementMaxLabel,greenEnhencementShowNumberLabel,greenIllustrationLabel;
	//shared_ptr<QLabel> blueEnhencementMinLabel,blueEnhencementMaxLabel,blueEnhencementShowNumberLabel,blueIllustrationLabel;
	shared_ptr<QRadioButton> dodgeRadioButton,deepenRadioButton;
	//for regionExtraction
	shared_ptr<QCheckBox> isHold;
	void updateShowNumberLabel();
public slots:
	void isHoldChanged();
protected:
	void resizeEvent(QResizeEvent *ev);
private:
	void initWidget();
	LocalEnhencementLabel *label;
};
#endif