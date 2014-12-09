#ifndef INTERACTIVE_COLOR_CORRECTION_H
#define INTERACTIVE_COLOR_CORRECTION_H
#include "header.h"
class InteractiveColorCorrectionWidget:public QWidget
{
public:
	InteractiveColorCorrectionWidget(QWidget *parent=0);

	shared_ptr<QSlider> redSlider,brightnessSlider,yellowSlider;
	shared_ptr<QLabel> redMinLabel,redMaxLabel,brightnessMinLabel,brightnessMaxLabel,yellowMinLabel,yellowMaxLabel;
	shared_ptr<QLabel> redIllustrationLabel,yellowIllustrationLabel,brightnessIllustrationLabel;
	shared_ptr<QLabel> redShowCurrentNumberLabel,yellowShowCurrentNumberLabel,brightnessShowCurrentNumberLabel;
	void updateShowCurrentNumberLabel();
protected:
	void resizeEvent(QResizeEvent *ev);
private:
	void initWidget();
};
#endif