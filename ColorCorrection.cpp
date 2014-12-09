#include "ColorCorrection.h"
#include "parameters.h"
ColorCorrectionThread::ColorCorrectionThread(Mat &_srcMat,Mat& _faceMask,Mat &_resultMat,double _mean,int _channel):srcMat(_srcMat),faceMask(_faceMask),resultMat(_resultMat),mean(_mean),channel(_channel)
{

}
ColorCorrection::ColorCorrection(Mat &_srcMat,Mat& _faceMask,Mat &_resultMat,double _mean,int _channel):srcMat(_srcMat),faceMask(_faceMask),resultMat(_resultMat),mean(_mean),channel(_channel)
{

}
void ColorCorrection::automaticColorCorrection()
{
	int w=srcMat.cols,h=srcMat.rows;
	double his[256]={0},dCandidate[256];
	unsigned int pixelNumber=0;
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(FACE_PIXEL_VALUE==faceMask.at<uchar>(i,j))
			{
				pixelNumber++;
				his[srcMat.at<Vec3b>(i,j)[channel]]++;
			}
		}
		double sum1,sum2;
		sum1=0;
		sum2=mean*pixelNumber/255.0;
		for(int i=0;i<256;++i)
		{
			double x=i/255.0;
			sum1+=(x*x-x)*his[i];
			sum2-=(x*his[i]);
		}
		double a=sum2/sum1,b=1-a;
		double pixelValue,temporary;
		uchar mappingTabel[256];
		for(unsigned int i=0;i<256;++i)
		{
			pixelValue=i/255.0;
			temporary=255*(a*pixelValue*pixelValue+b*pixelValue);
			temporary=(temporary>255)?255:temporary;
			temporary=(temporary<0)?0:temporary;
			mappingTabel[i]=(unsigned char)temporary;
		}
		for(int i=0;i<w;++i)
			for(int j=0;j<h;++j)
			{
				resultMat.at<Vec3b>(j,i)[channel]=mappingTabel[srcMat.at<Vec3b>(j,i)[channel]];
			}
}
void ColorCorrectionThread::run()
{
	int w=srcMat.cols,h=srcMat.rows;
	double his[256]={0},dCandidate[256];
	unsigned int pixelNumber=0;
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(FACE_PIXEL_VALUE==faceMask.at<uchar>(i,j))
			{
				pixelNumber++;
				his[srcMat.at<Vec3b>(i,j)[channel]]++;
			}
		}
	double sum1,sum2;
	sum1=0;
	sum2=mean*pixelNumber/255.0;
	for(int i=0;i<256;++i)
	{
		double x=i/255.0;
		sum1+=(x*x-x)*his[i];
		sum2-=(x*his[i]);
	}
	double a=sum2/sum1,b=1-a;
	double pixelValue,temporary;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			pixelValue=srcMat.at<Vec3b>(j,i)[channel]/255.0;
			temporary=255*(a*pixelValue*pixelValue+b*pixelValue);
			temporary=(temporary>255)?255:temporary;
			temporary=(temporary<0)?0:temporary;
			resultMat.at<Vec3b>(j,i)[channel]=(uchar)temporary;
		}
	/*for(int i=1;i<255;++i)
	{
		c=i/255.0;
		sum1=0;
		sum2=mean*pixelNumber/255.0;
		for(int j=0;j<256;++j)
		{
			sum1+=his[j]*(j/255.0)*(j/255.0-1)/(c*c-c);
			sum2+=his[j]*c*(j/255.0)*(j/255.0-c)/(c*c-c);
		}
		dCandidate[i]=sum2/sum1;
	}
	int t=getOptimalC(dCandidate);
	c=t/255.0;
	d=dCandidate[t];
	double pixelValue,temporary;
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			pixelValue=srcMat.at<Vec3b>(i,j)[channel]/255.0;
			temporary=((d-c)/(c*c-c)*pixelValue*pixelValue+(c*c-d)/(c*c-c)*pixelValue)*255;
				temporary=(temporary>255)?255:temporary;
			temporary=(temporary<0)?0:temporary;
			resultMat.at<Vec3b>(i,j)[channel]=(uchar)temporary;
		}*/
}
