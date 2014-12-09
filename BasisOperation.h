#ifndef BASIS_OPERATION_H
#define BASIS_OPERATION_H
#include "header.h"
class BasisOperation
{
public:
	//calculate gradient
	void static modifySaturationOrLightness(Mat &hsvMat,int channel,float diff);
	void static adjustBrightness(Mat &srcMat,Mat &resultMat,Mat &faceMask,int brightnessMeans);
	double static gradient(Mat &srcMat,int x,int y,int channel,unsigned char orientation,unsigned char mode);
	void static mat2QImage(Mat &mat,QImage &img);
	void static qimage2Mat(QImage &img,Mat &mat);
	void static qimage2OneChannelMat(QImage &img,unsigned int imagePixelValue,Mat &mat,unsigned char matPixelValue);
	void static sharpEffect(Mat &srcMat,Mat &resultMat);
	void static localEnhencementUsingMappingMethod(Mat &resultMat,Mat * mask,double x,double y);
	void static localEnhencementUsingMappingMethod(Mat &resultMat,Mat *mask,double x,double y,int channal);
	void static regionExtraction(Mat *srcMat,Mat *regionMask,int threhold,Rect &region,int startX,int startY);
	void static ColorBalance(Mat &srcMat,Mat &result,double red,double green,double blue);
	bool static pixelIsBoundary(Mat &img,int x,int y);
	void static colorLevel(Mat &srcMat,Mat &resultMat,unsigned char low,unsigned char high,int channel,unsigned char mid);
	void static colorLevel(Mat &srcMat,Mat &resultMat,unsigned char low,unsigned char high,unsigned char mid);
	unsigned char static grayLevel(Mat &srcMat,Mat &faceMask,Rect &face,unsigned char &low,unsigned char &high);
	void static getLowAndHigh(Mat &srcMat,unsigned char &low,unsigned char &high);
	bool static faceNeedColorCorrection(Mat &srcMat,Mat &faceMask,Rect &face);
	unsigned char static getColorLevelValue(unsigned char low,unsigned char high,unsigned char mid,unsigned char pixelValue);
	//regionAutomaticAdjust
	bool static regionNeedAdjust(Mat &srcMat,Mat &resultMat,int x1,int y1,int x2,int y2,int gridWidth,Rect &face,Mat &faceMask,int *labels,int labelsWidth,int labelsHeight,const double threshold=0.2);
	bool static regionStatistics(Mat &srcMat,int x,int y,int gridWidth,int *labels,int labelsWidth,int labelsHeight,int centerLabel,Rect &face,Mat &faceMask,double &mean,double &pixelNumber,Mat &regionMask,int *lightnessHis);
	void static regionColorTransfer(Mat &srcMat,Mat &targetMat,Mat &resultMat,Mat &srcRegionMask,Mat &targetRegionMask);
	void static poissonEditing(Mat &srcMat,Mat &resultMat,Mat &regionMask,int *position,int regionPixelnumber,int channel,double lowPixelValueBoundary,double highPixelValueBoundary);
	void static poissonEditing(Mat &srcMat,Mat &resultMat,Mat &regionMask,int *position,int regionPixelnumber,int channel,int faceImageWidth,Rect r);
	int static searchCul(double *culHis,double value,int bins);
	//only for hsv 
	double static thresholdOstuMethod(Mat &hsvMat,Mat &faceMask,Rect face,int channel);
private:
	//work with regionExtraction
	bool static insertIntoQueue(Mat *srcMat,Mat *regionMask,int threhold,int x1,int y1,int x2,int y2,queue<QPoint> &pixelQueue);
};
#endif