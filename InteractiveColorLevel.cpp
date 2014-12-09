#include "InteractiveColorLevel.h"
InteractiveColorLevelWidget::InteractiveColorLevelWidget(QWidget *parent/* =0 */):QWidget(parent)
{

}
void InteractiveColorLevelWidget::initWidget()
{
	int w=this->width(),h=this->height();
	redSlider=shared_ptr<QSlider>(new QSlider(this));
	redShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	redMinLabel=shared_ptr<QLabel>(new QLabel(this));
	redMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	redIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	saturationSlider=shared_ptr<QSlider>(new QSlider(this));
	saturationShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	saturationMinLabel=shared_ptr<QLabel>(new QLabel(this));
	saturationMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	saturationIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	lightnessSlider=shared_ptr<QSlider>(new QSlider(this));
	lightnessShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	lightnessMinLabel=shared_ptr<QLabel>(new QLabel(this));
	lightnessMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	lightnessIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	contrastSlider=shared_ptr<QSlider>(new QSlider(this));
	contrastShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	contrastMinLabel=shared_ptr<QLabel>(new QLabel(this));
	contrastMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	contrastIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));

	redSlider->setGeometry((w>>1)-80,(h>>2)-50,160,20);
	redSlider->setRange(0,100);
	redSlider->setSliderPosition(50);
	redSlider->setOrientation(Qt::Horizontal);
	redMinLabel->setGeometry(redSlider->x()-10,redSlider->y(),6,12);
	redMinLabel->setText("-");
	redMaxLabel->setGeometry(redSlider->x()+redSlider->width()+10,redSlider->y(),6,12);
	redMaxLabel->setText("+");
	redShowCurrentNumberLabel->setGeometry(redSlider->x()+(redSlider->width()>>1)-10,redSlider->y()+redSlider->height()+10,30,12);
	redShowCurrentNumberLabel->setText("127");

	saturationSlider->setGeometry((w>>1)-80,(h>>1)-50,160,20);
	saturationSlider->setRange(0,100);
	saturationSlider->setSliderPosition(50);
	saturationSlider->setOrientation(Qt::Horizontal);
	saturationIllustrationLabel->setGeometry((w>>1)-30,saturationSlider->y()-20,60,12);
	saturationIllustrationLabel->setText("saturation");
	saturationMinLabel->setGeometry(saturationSlider->x()-10,saturationSlider->y(),6,12);
	saturationMinLabel->setText("-");
	saturationMaxLabel->setGeometry(saturationSlider->x()+saturationSlider->width()+10,saturationSlider->y(),6,12);
	saturationMaxLabel->setText("+");
	saturationShowCurrentNumberLabel->setGeometry(saturationSlider->x()+(saturationSlider->width()>>1)-10,saturationSlider->y()+saturationSlider->height()+10,30,12);
	saturationShowCurrentNumberLabel->setText("0.00");

	lightnessSlider->setGeometry((w>>1)-80,(h*0.75)-50,160,20);
	lightnessSlider->setRange(0,100);
	lightnessSlider->setSliderPosition(50);
	lightnessSlider->setOrientation(Qt::Horizontal);
	lightnessIllustrationLabel->setGeometry((w>>1)-30,lightnessSlider->y()-20,60,12);
	lightnessIllustrationLabel->setText("lightness");
	lightnessMinLabel->setGeometry(lightnessSlider->x()-10,lightnessSlider->y(),6,12);
	lightnessMinLabel->setText("-");
	lightnessMaxLabel->setGeometry(lightnessSlider->x()+lightnessSlider->width()+10,lightnessSlider->y(),6,12);
	lightnessMaxLabel->setText("+");
	lightnessShowCurrentNumberLabel->setGeometry(lightnessSlider->x()+(lightnessSlider->width()>>1)-10,lightnessSlider->y()+lightnessSlider->height()+10,30,12);
	lightnessShowCurrentNumberLabel->setText("0.00");

	contrastSlider->setGeometry((w>>1)-80,h-50,160,20);
	contrastSlider->setRange(0,100);
	contrastSlider->setSliderPosition(50);
	contrastSlider->setOrientation(Qt::Horizontal);
	contrastIllustrationLabel->setGeometry((w>>1)-30,contrastSlider->y()-20,60,12);
	contrastIllustrationLabel->setText("contrast");
	contrastMinLabel->setGeometry(contrastSlider->x()-10,contrastSlider->y(),6,12);
	contrastMinLabel->setText("-");
	contrastMaxLabel->setGeometry(contrastSlider->x()+contrastSlider->width()+10,contrastSlider->y(),6,12);
	contrastMaxLabel->setText("+");
	contrastShowCurrentNumberLabel->setGeometry(contrastSlider->x()+(contrastSlider->width()>>1)-10,contrastSlider->y()+contrastSlider->height()+10,30,12);
	contrastShowCurrentNumberLabel->setText("0.00");
}
void InteractiveColorLevelWidget::resizeEvent(QResizeEvent *ev)
{
	initWidget();
}
void InteractiveColorLevelWidget::updateShowCurrentNumberLabel()
{
	redShowCurrentNumberLabel->setText(QString::number((unsigned char)(redSlider->value()*2.55)));
	saturationShowCurrentNumberLabel->setText(QString::number((saturationSlider->value()-50)*0.01));
	lightnessShowCurrentNumberLabel->setText(QString::number((lightnessSlider->value()-50)*0.01));
	contrastShowCurrentNumberLabel->setText(QString::number((contrastSlider->value()-50)*0.01));
}