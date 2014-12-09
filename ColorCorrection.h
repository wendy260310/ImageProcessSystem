#ifndef _COLOR_CORRECTION_H
#define _COLOR_CORRECTION_H
#include "header.h"
class ColorCorrectionThread:public QThread
{
public:
	ColorCorrectionThread(Mat &_srcMat,Mat& _faceMask,Mat &_resultMat,double _mean,int _channel);
protected:
	void run();
private:
	Mat &srcMat,&faceMask,&resultMat;
	int channel;
	double mean,c,d;
};
class ColorCorrection
{
public:
	ColorCorrection(Mat &_srcMat,Mat& _faceMask,Mat &_resultMat,double _mean,int _channel);
	void automaticColorCorrection();
private:
	Mat &srcMat,&faceMask,&resultMat;
	int channel;
	double mean,c,d;
};
#endif