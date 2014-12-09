#include "HighlightLabel.h"
#include "parameters.h"
#ifndef EXPORT_DLL
HighLightLabel::HighLightLabel(QWidget *parent):InteractiveImageLabel(parent)
{

}
void HighLightLabel::mouseReleaseEvent(QMouseEvent *ev)
{
	InteractiveImageLabel::mouseReleaseEvent(ev);
	if(ev->button()==Qt::LeftButton&&startpos!=ev->pos())
	{
		emit interactiveHighlightFinished();
	}
}
#endif
