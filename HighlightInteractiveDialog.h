#ifndef HIGHLIGHT_INTERACTIVE_DIALOG_H
#define HIGHLIGHT_INTERACTIVE_DIALOG_H
#include "e:\qt\4.8.2\src\gui\dialogs\qdialog.h"
#include "ui_HighlightInteractiveDialog.h"
#include "faceDetector.h"
#include "highlightDetection.h"
#include "highlightRemoval.h"
#include "BasisOperation.h"
class HighlightInteractiveDialog :
	public QDialog
{
	Q_OBJECT
public:
	QImage & getMask();
	HighlightInteractiveDialog();
	void setVariable(QImage *_srcImg,Mat *_srcMat,Mat *faceMask,Rect _face,Mat *_highlightMat,Mat *_resultMat);
	~HighlightInteractiveDialog(void);
protected:
	void closeEvent(QCloseEvent *ev);
public slots:
	void resetMask();
	void highlightRemoval();
	void highlightParametersChanged(int value);
	void updateGroupBox();
private:
	void highlightQImage2Mat();
	QImage *srcImg;
	Mat *srcMat;
	Mat *resultMat;
	QImage *resultImage;
	Rect face;
	Mat *highlightMask;
	Mat *faceMask;
	Ui::Dialog ui;
	bool usingBrush;
};
#endif
