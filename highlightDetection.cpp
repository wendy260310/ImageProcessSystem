#include "highlightDetection.h"
void HighLightDetection::highlightDetection(Mat &highlightMask,Mat &srcMat,Mat &faceMask,unsigned char mode,Rect &r)
{
	if(mode&HIGHLIGHT_GLOSSY_REFLECTION_METHOD)
	{
		glossyReflectionMethod(highlightMask,srcMat,faceMask);
	}
	if(mode&HIGHLIGHT_VALUE_SATURATION_METHOD)
	{
		valueAndSaturation(highlightMask,srcMat,faceMask,r);
	}
	if(mode&HIGHLIGHT_LOCAL_GRADIENT_METHOD)
	{
		localGradient(highlightMask,srcMat,faceMask,r);
	}
}
void HighLightDetection::localGradient(Mat &highlightMask,Mat &srcMat,Mat &faceMask,Rect &r)
{
	int x=r.x,y=r.y,w=r.width,h=r.height;
	double gx,gy,A,B,C;
	Mat hsvMat(srcMat.rows,srcMat.cols,CV_32FC3);
	ColorSpaceTransition::rgb2Hsv(srcMat,hsvMat);
	for(int i=x;i<x+w;++i)
		for(int j=y;j<y+h;++j)
		{
			if(faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE)
			{
				gx=hsvMat.at<Vec3f>(j,i)[0]-hsvMat.at<Vec3f>(j,i-1)[0];
				gy=hsvMat.at<Vec3f>(j,i)[0]-hsvMat.at<Vec3f>(j-1,i)[0];
				if(!(gx>0)&&!(gx<0)&&!(gy>0)&&!(gy<0))
				{
						A=2*hsvMat.at<Vec3f>(j,i)[0]-hsvMat.at<Vec3f>(j,i+1)[0]-hsvMat.at<Vec3f>(j,i-1)[0];
						C=2*hsvMat.at<Vec3f>(j,i)[0]-hsvMat.at<Vec3f>(j+1,i)[0]-hsvMat.at<Vec3f>(j-1,i)[0];
						B=hsvMat.at<Vec3f>(j+1,i)[0]-hsvMat.at<Vec3f>(j+1,i-1)[0]-hsvMat.at<Vec3f>(j,i)[0]+hsvMat.at<Vec3f>(j,i-1)[0];
						if((B*B-A*C)<0&&A<0)
							highlightMask.at<uchar>(j,i)=HIGHLIGHT_PIXEL_VALUE;
				}
			}
		}
}
void HighLightDetection::valueAndSaturation(Mat &highlightMask,Mat &srcMat,Mat &faceMask,Rect &r)
{
	int x=r.x,y=r.y,w=r.width,h=r.height;
	Mat hsvMat(srcMat.rows,srcMat.cols,CV_32FC3);
	ColorSpaceTransition::rgb2Hsv(srcMat,hsvMat);
	double s,v,sOstu,vOstu;
	sOstu=BasisOperation::thresholdOstuMethod(hsvMat,faceMask,r,1);
	vOstu=BasisOperation::thresholdOstuMethod(hsvMat,faceMask,r,0);
	for(int i=x;i<w+x;++i)
		for(int j=y;j<h+y;++j)
		{
			if(faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE)
			{
				s=hsvMat.at<Vec3f>(j,i)[1];
				v=hsvMat.at<Vec3f>(j,i)[0];
				if(s<=sOstu&&v>=vOstu)
				{
					highlightMask.at<uchar>(j,i)=HIGHLIGHT_PIXEL_VALUE;
				}
			}
		}
}
//discard!
void HighLightDetection::glossyReflectionMethod(Mat &highlightMask,Mat &srcMat,Mat &faceMask)
{
	int w=srcMat.cols,h=srcMat.rows;
	double thd,Y,Ymax,Ymin,R,G,B,Cr,Cb;
	Ymin=300;
	Ymax=-100;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			if(faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE)
			{
				R=srcMat.at<Vec3b>(j,i)[2];
				G=srcMat.at<Vec3b>(j,i)[1];
				B=srcMat.at<Vec3b>(j,i)[0];
				Y=0.257*R+0.504*G+0.098*B+16;
				Ymax=Ymax>Y?Ymax:Y;
				Ymin=Ymin<Y?Ymin:Y;
			}
		}
	thd=(Ymax-Ymin)*0.8+Ymin;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			if(faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE)
			{
				R=srcMat.at<Vec3b>(j,i)[2];
				G=srcMat.at<Vec3b>(j,i)[1];
				B=srcMat.at<Vec3b>(j,i)[0];
				Y=0.257*R+0.504*G+0.098*B+16;
				if(Y>thd)
				{
						highlightMask.at<uchar>(j,i)=HIGHLIGHT_PIXEL_CANDIDATE;
				}
			}
		}
}
