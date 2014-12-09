#include "InteractiveHighlightWidget.h"
InteractiveHighlightWidget::InteractiveHighlightWidget(QWidget *parent):QWidget(parent)
{

}
void InteractiveHighlightWidget::resizeEvent(QResizeEvent *ev)
{
	initWidget();
}
void InteractiveHighlightWidget::initWidget()
{
	int w=this->width(),h=this->height();
	possionMethodRadioButton=shared_ptr<QRadioButton>(new QRadioButton(this));
	inpaintingMethodRadioButton=shared_ptr<QRadioButton>(new QRadioButton(this));
	possionMethodRadioButton->setText("Possion");
	possionMethodRadioButton->setGeometry((w>>1)-80,h>>2,80,16);
	possionMethodRadioButton->setChecked(true);
	inpaintingMethodRadioButton->setText("Inpainting");
	inpaintingMethodRadioButton->setGeometry(possionMethodRadioButton->x()+90,possionMethodRadioButton->y(),80,16);
}