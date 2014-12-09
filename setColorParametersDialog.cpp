#include "setColorParametersDialog.h"
setColorParametersDialog::setColorParametersDialog():ui(new Ui::colorParametersDialog())
{
	ui->setupUi(this);
	connecting();
}
void setColorParametersDialog::connecting()
{
	connect(ui->brightnessSlider,SIGNAL(valueChanged(int)),this,SLOT(setbrightness(int)));
	connect(ui->redSlider,SIGNAL(valueChanged(int)),this,SLOT(setdata1(int)));
	connect(ui->yellowSlider,SIGNAL(valueChanged(int)),this,SLOT(setdata4(int)));
}
int setColorParametersDialog::getTolerance()
{
	QString s=ui->toleranceLineEdit->text();
	int result=0;
	if(!s.isNull())
	{
		result=s.toInt();
	}
	return result;
}
int setColorParametersDialog::getFeather()
{
	QString s=ui->featherLineEdit->text();
	int result=0;
	if(!s.isNull())
	{
		result=s.toInt();
	}
	return result;
}
void setColorParametersDialog::updateLabel(QLabel *l,double value)
{
	l->setText(QString::number(value));
}
void setColorParametersDialog::checkParameters()
{
	double data1=ui->redSlider->value()*0.01;
	double data4=ui->yellowSlider->value()*0.01;
	if((data1*(data4-1))>0.14)
		ui->okButton->setEnabled(false);
	else
		ui->okButton->setEnabled(true);
}
void setColorParametersDialog::setdata1(int value)
{
	updateLabel(ui->redLabel,value);
	checkParameters();
}
void setColorParametersDialog::setdata4(int value)
{
	updateLabel(ui->yellowLabel,value);
	checkParameters();
}
void setColorParametersDialog::setbrightness(int value)
{
	updateLabel(ui->brightnessLabel,value);
	checkParameters();
}