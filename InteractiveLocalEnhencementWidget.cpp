#include "InteractiveLocalEnhencementWidget.h"
#include "LocalEnhencementLabel.h"
InteractiveLocalEnhencementWidget::InteractiveLocalEnhencementWidget(QWidget *parent,LocalEnhencementLabel *_label):QWidget(parent),label(_label)
{
	//connect(isHold.get(),SIGNAL(clicked()),this,SLOT(isHoldChanged()));
}
void InteractiveLocalEnhencementWidget::updateShowNumberLabel()
{
	redEnhencementShowNumberLabel->setText(QString::number((redEnhencementSlider->value()-50)*0.01));
//  greenEnhencementShowNumberLabel->setText(QString::number((greenEnhencementSlider->value()-50)*0.01));
//	blueEnhencementShowNumberLabel->setText(QString::number((blueEnhencementSlider->value()-50)*0.01));
}
void InteractiveLocalEnhencementWidget::initWidget()
{
	int w=this->width(),h=this->height();
	//redEnhencement
	redEnhencementSlider=shared_ptr<QSlider>(new QSlider(this));
	redEnhencementMinLabel=shared_ptr<QLabel>(new QLabel(this));
	redEnhencementMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	redEnhencementShowNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	redIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	redEnhencementSlider->setGeometry((w>>1)-80,(h>>1)-10,160,20);
	redEnhencementSlider->setRange(0,100);
	redEnhencementSlider->setSliderPosition(50);
	redEnhencementSlider->setOrientation(Qt::Horizontal);
	redIllustrationLabel->setText("Lightness");
	redIllustrationLabel->setGeometry((w>>1)-27,redEnhencementSlider->y()-20,54,12);
	redEnhencementMinLabel->setGeometry(redEnhencementSlider->x()-10,redEnhencementSlider->y(),6,12);
	redEnhencementMinLabel->setText("-");
	redEnhencementMaxLabel->setGeometry(redEnhencementSlider->x()+redEnhencementSlider->width()+10,redEnhencementSlider->y(),6,12);
	redEnhencementMaxLabel->setText("+");
	redEnhencementShowNumberLabel->setGeometry(redEnhencementSlider->x()+(redEnhencementSlider->width()>>1)-10,redEnhencementSlider->y()+redEnhencementSlider->height()+10,30,12);
	redEnhencementShowNumberLabel->setText("0.000");
	//blueEnhencement
	//blueEnhencementSlider=shared_ptr<QSlider>(new QSlider(this));
	//blueEnhencementMinLabel=shared_ptr<QLabel>(new QLabel(this));
	//blueEnhencementMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	//blueEnhencementShowNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	//blueIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	//blueEnhencementSlider->setGeometry(redEnhencementSlider->x(),redEnhencementSlider->y()+100,160,20);
	//blueEnhencementSlider->setRange(0,100);
	//blueEnhencementSlider->setSliderPosition(50);
	//blueEnhencementSlider->setOrientation(Qt::Horizontal);
	//blueEnhencementSlider->setEnabled(false);
	//blueIllustrationLabel->setText("Blue");
	//blueIllustrationLabel->setGeometry((w>>1)-12,blueEnhencementSlider->y()-20,24,12);
	//blueEnhencementMinLabel->setText("-");
	//blueEnhencementMinLabel->setGeometry(blueEnhencementSlider->x()-10,blueEnhencementSlider->y(),6,12);
	//blueEnhencementMaxLabel->setText("+");
	//blueEnhencementMaxLabel->setGeometry(blueEnhencementSlider->x()+blueEnhencementSlider->width()+10,blueEnhencementSlider->y(),6,12);
	//blueEnhencementShowNumberLabel->setGeometry((w>>1)-15,blueEnhencementSlider->y()+blueEnhencementSlider->height()+10,30,12);
	//blueEnhencementShowNumberLabel->setText("0.000");
	//green
	//greenEnhencementSlider=shared_ptr<QSlider>(new QSlider(this));
	//greenEnhencementMinLabel=shared_ptr<QLabel>(new QLabel(this));
	//greenEnhencementMaxLabel=shared_ptr<QLabel>(new QLabel(this));
	//greenEnhencementShowNumberLabel=shared_ptr<QLabel>(new QLabel(this));
	//greenIllustrationLabel=shared_ptr<QLabel>(new QLabel(this));
	//greenEnhencementSlider->setGeometry(blueEnhencementSlider->x(),blueEnhencementSlider->y()+100,160,20);
	//greenEnhencementSlider->setRange(0,100);
	//greenEnhencementSlider->setSliderPosition(50);
	//greenEnhencementSlider->setOrientation(Qt::Horizontal);
	//greenEnhencementSlider->setEnabled(false);
	//greenIllustrationLabel->setText("Green");
	//greenIllustrationLabel->setGeometry((w>>1)-15,greenEnhencementSlider->y()-20,30,12);
	//greenEnhencementMinLabel->setText("-");
	//greenEnhencementMinLabel->setGeometry(greenEnhencementSlider->x()-10,greenEnhencementSlider->y(),6,12);
	//greenEnhencementMaxLabel->setText("+");
	//greenEnhencementMaxLabel->setGeometry(greenEnhencementSlider->x()+greenEnhencementSlider->width()+10,greenEnhencementSlider->y(),6,12);
	//greenEnhencementShowNumberLabel->setGeometry((w>>1)-15,greenEnhencementSlider->y()+greenEnhencementSlider->height()+10,30,12);
	//greenEnhencementShowNumberLabel->setText("0.000");
	//RatioButton
	dodgeRadioButton=shared_ptr<QRadioButton>(new QRadioButton(this));
	dodgeRadioButton->setGeometry(redEnhencementSlider->x(),redEnhencementSlider->y()-(h>>2),80,16);
	dodgeRadioButton->setText("dodge");
	dodgeRadioButton->setChecked(true);

	deepenRadioButton=shared_ptr<QRadioButton>(new QRadioButton(this));
	deepenRadioButton->setGeometry(dodgeRadioButton->x()+90,dodgeRadioButton->y(),80,16);
	deepenRadioButton->setText("deepen");

	isHold=shared_ptr<QCheckBox>(new QCheckBox(this));
	isHold->setChecked(false);
	isHold->setGeometry(redEnhencementSlider->x(),h-(h>>2),120,16);
	isHold->setText("Region Holding");
}
void InteractiveLocalEnhencementWidget::resizeEvent(QResizeEvent *ev)
{
	initWidget();
}
void InteractiveLocalEnhencementWidget::isHoldChanged()
{
	label->setRegionIsHolding(isHold->isChecked());
}