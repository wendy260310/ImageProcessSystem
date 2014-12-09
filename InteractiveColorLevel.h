#ifndef INTERACTIVE_COLOR_LEVEL_H
#define INTERACTIVE_COLOR_LEVEL_H
#include "header.h"
class InteractiveColorLevelWidget:public QWidget
{
public:
	InteractiveColorLevelWidget(QWidget *parent=0);
	shared_ptr<QSlider> redSlider;
	shared_ptr<QLabel> redMinLabel,redMaxLabel;
	shared_ptr<QLabel> redShowCurrentNumberLabel;
	shared_ptr<QLabel> redIllustrationLabel;

	shared_ptr<QSlider> saturationSlider;
	shared_ptr<QLabel> saturationMinLabel,saturationMaxLabel;
	shared_ptr<QLabel> saturationShowCurrentNumberLabel;
	shared_ptr<QLabel> saturationIllustrationLabel;

	shared_ptr<QSlider> lightnessSlider;
	shared_ptr<QLabel> lightnessMinLabel,lightnessMaxLabel;
	shared_ptr<QLabel> lightnessShowCurrentNumberLabel;
	shared_ptr<QLabel> lightnessIllustrationLabel;

	shared_ptr<QSlider> contrastSlider;
	shared_ptr<QLabel> contrastMinLabel,contrastMaxLabel;
	shared_ptr<QLabel> contrastShowCurrentNumberLabel;
	shared_ptr<QLabel> contrastIllustrationLabel;
	void updateShowCurrentNumberLabel();
protected:
	void resizeEvent(QResizeEvent *ev);
private:
	void initWidget();
};
#endif