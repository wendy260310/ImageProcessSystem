#ifndef EXPORT_DLL
#include "InteractiveColorBalanceWidget.h"
#include "parameters.h"
#include "InteractiveColorCorrectionWidget.h"
#include "parameters.h"
InteractiveColorBalanceWidget::InteractiveColorBalanceWidget(QWidget *parent):QWidget(parent)
{

}
void InteractiveColorBalanceWidget::initWidget()
{
	//init
	int w=this->width(),h=this->height();
	redSlider=shared_ptr<QSlider>(new QSlider(this));
	blueSlider=shared_ptr<QSlider>(new QSlider(this));
	greenSlider=shared_ptr<QSlider>(new QSlider(this));
	redMinLabel=shared_ptr<QLabel>(new QLabel(this));
	redMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	greenMinLabel=shared_ptr<QLabel>(new QLabel(this));
	greenMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	blueMinLabel=shared_ptr<QLabel>(new QLabel(this));
	blueMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	redIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	greenIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	blueIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	redShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	greenShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	blueShowCurrentNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	//set geometry
	//blue
	blueIllustrationLabel->setGeometry((w>>1)-18,h>>3,36,12);
	blueIllustrationLabel->setText("blue");
	blueSlider->setGeometry((w>>1)-80,blueIllustrationLabel->y()+20,160,20);
	blueSlider->setRange(0,100);
	blueSlider->setSliderPosition(50);
	blueSlider->setOrientation(Qt::Horizontal);
	blueMinLabel->setGeometry(blueSlider->x()-20,blueSlider->y(),18,12);
	blueMinLabel->setText("-");
	blueMaxLabel->setGeometry(blueSlider->x()+blueSlider->width(),blueSlider->y(),18,12);
	blueMaxLabel->setText("+");
	blueShowCurrentNumberLabel->setGeometry((w>>1)-18,blueSlider->y()+blueSlider->height()+10,36,12);
	blueShowCurrentNumberLabel->setText("0.000");
	//red
	redIllustrationLabel->setGeometry((w>>1)-9,h*0.375,18,12);
	redIllustrationLabel->setText("red");
	redSlider->setGeometry((w>>1)-80,redIllustrationLabel->y()+20,160,20);
	redSlider->setRange(0,100);
	redSlider->setSliderPosition(50);
	redSlider->setOrientation(Qt::Horizontal);
	redMinLabel->setGeometry(redSlider->x()-20,redSlider->y(),18,12);
	redMinLabel->setText("-");
	redMaxLabel->setGeometry(redSlider->x()+redSlider->width(),redSlider->y(),18,12);
	redMaxLabel->setText("+");
	redShowCurrentNumberLabel->setGeometry((w>>1)-18,redSlider->y()+redSlider->height()+10,36,12);
	redShowCurrentNumberLabel->setText("0.000");
	//green
	greenIllustrationLabel->setGeometry((w>>1)-18,h*0.625,36,12);
	greenIllustrationLabel->setText("green");
	greenSlider->setGeometry((w>>1)-80,greenIllustrationLabel->y()+20,160,20);
	greenSlider->setRange(0,100);
	greenSlider->setSliderPosition(50);
	greenSlider->setOrientation(Qt::Horizontal);
	greenMinLabel->setGeometry(greenSlider->x()-20,greenSlider->y(),18,12);
	greenMinLabel->setText("-");
	greenMaxLabel->setGeometry(greenSlider->x()+greenSlider->width(),greenSlider->y(),18,12);
	greenMaxLabel->setText("+");
	greenShowCurrentNumberLabel->setGeometry((w>>1)-18,greenSlider->y()+greenSlider->height()+10,36,12);
	greenShowCurrentNumberLabel->setText("0.000");

}
void InteractiveColorBalanceWidget::resizeEvent(QResizeEvent *ev)
{
	initWidget();
}
void InteractiveColorBalanceWidget::updateShowCurrentNumberLabel()
{
	redShowCurrentNumberLabel->setText(QString::number(redSlider->value()*0.01-0.5));
	greenShowCurrentNumberLabel->setText(QString::number(greenSlider->value()*0.01-0.5));
	blueShowCurrentNumberLabel->setText(QString::number(blueSlider->value()*0.01-0.5));
}
#endif