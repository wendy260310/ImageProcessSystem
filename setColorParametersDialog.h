#ifndef SET_COLOR_PARAMETERS_DIALOG_H
#define SET_COLOR_PARAMETERS_DIALOG_H
#include "ui_setColorParameters.h"
#include "header.h"
class setColorParametersDialog:public QDialog
{
	Q_OBJECT
public:
	setColorParametersDialog();
	~setColorParametersDialog(){};
	int getData1()const{return ui->redSlider->value();}
	int getData4()const{return ui->yellowSlider->value();}
	int getBrightness() const{return ui->brightnessSlider->value();}
	int getTolerance();
	int getFeather();
	QPushButton* getOKAction(){return ui->okButton;}
public slots:
	void setdata1(int value);
	void setdata4(int value);
	void setbrightness(int value);
private:
	void connecting();
	void updateLabel(QLabel *l,double value);
	void checkParameters();

	unique_ptr< Ui::colorParametersDialog > ui;
};
#endif