#include "InteractiveColorCorrectionWidget.h"
#include "parameters.h"
InteractiveColorCorrectionWidget::InteractiveColorCorrectionWidget(QWidget *parent):QWidget(parent)
{

}
void InteractiveColorCorrectionWidget::initWidget()
{
	//init
	int w=this->width(),h=this->height();
	redSlider=shared_ptr<QSlider>(new QSlider(this));
	brightnessSlider=shared_ptr<QSlider>(new QSlider(this));
	yellowSlider=shared_ptr<QSlider>(new QSlider(this));
	redMinLabel=shared_ptr<QLabel>(new QLabel(this));
	redMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	yellowMinLabel=shared_ptr<QLabel>(new QLabel(this));
	yellowMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	brightnessMinLabel=shared_ptr<QLabel>(new QLabel(this));
	brightnessMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	redIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	yellowIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	brightnessIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	redShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	yellowShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	brightnessShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	//set geometry
	//brightness
	brightnessIllustrationLabel->setGeometry((w>>1)-30,h>>3,60,12);
	brightnessIllustrationLabel->setText("brightness");
	brightnessSlider->setGeometry((w>>1)-80,brightnessIllustrationLabel->y()+20,160,20);
	brightnessSlider->setRange(170,190);
	brightnessSlider->setSliderPosition(173);
	brightnessSlider->setOrientation(Qt::Horizontal);
	brightnessMinLabel->setGeometry(brightnessSlider->x()-20,brightnessSlider->y(),18,12);
	brightnessMinLabel->setText("170");
	brightnessMaxLabel->setGeometry(brightnessSlider->x()+brightnessSlider->width(),brightnessSlider->y(),18,12);
	brightnessMaxLabel->setText("190");
	brightnessShowCurrentNumberLabel->setGeometry((w>>1)-9,brightnessSlider->y()+brightnessSlider->height()+10,18,12);
	brightnessShowCurrentNumberLabel->setText("173");
	//red
	redIllustrationLabel->setGeometry((w>>1)-9,h*0.375,18,12);
	redIllustrationLabel->setText("red");
	redSlider->setGeometry((w>>1)-80,redIllustrationLabel->y()+20,160,20);
	redSlider->setRange(116,129);
	redSlider->setSliderPosition(120);
	redSlider->setOrientation(Qt::Horizontal);
	redMinLabel->setGeometry(redSlider->x()-20,redSlider->y(),18,12);
	redMinLabel->setText("116");
	redMaxLabel->setGeometry(redSlider->x()+redSlider->width(),redSlider->y(),18,12);
	redMaxLabel->setText("129");
	redShowCurrentNumberLabel->setGeometry((w>>1)-9,redSlider->y()+redSlider->height()+10,18,12);
	redShowCurrentNumberLabel->setText("120");
	//yellow
	yellowIllustrationLabel->setGeometry((w>>1)-18,h*0.625,36,12);
	yellowIllustrationLabel->setText("yellow");
	yellowSlider->setGeometry((w>>1)-80,yellowIllustrationLabel->y()+20,160,20);
	yellowSlider->setRange(103,116);
	yellowSlider->setSliderPosition(110);
	yellowSlider->setOrientation(Qt::Horizontal);
	yellowMinLabel->setGeometry(yellowSlider->x()-20,yellowSlider->y(),18,12);
	yellowMinLabel->setText("103");
	yellowMaxLabel->setGeometry(yellowSlider->x()+yellowSlider->width(),yellowSlider->y(),18,12);
	yellowMaxLabel->setText("116");
	yellowShowCurrentNumberLabel->setGeometry((w>>1)-9,yellowSlider->y()+yellowSlider->height()+10,18,12);
	yellowShowCurrentNumberLabel->setText("110");

}
void InteractiveColorCorrectionWidget::resizeEvent(QResizeEvent *ev)
{
	initWidget();
}
void InteractiveColorCorrectionWidget::updateShowCurrentNumberLabel()
{
	redShowCurrentNumberLabel->setText(QString::number(redSlider->value()));
	yellowShowCurrentNumberLabel->setText(QString::number(yellowSlider->value()));
	brightnessShowCurrentNumberLabel->setText(QString::number(brightnessSlider->value()));
}