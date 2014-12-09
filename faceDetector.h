#ifndef FACE_DETECTOR_H
#define FACE_DETECTOR_H
#include "parameters.h"
#include "header.h"
#include "ColorSpaceTransitionClass.h"
class faceDetector
{
public:
	void static loadCascade();
	void static detectingFace(Mat &srcMat,Mat &faceMask,unsigned char mode,Rect &face);
	Rect static detectingFacesUsingOpencv(Mat &srcMat);
protected:
	faceDetector(void){}
	~faceDetector(void){}
private:
	void static detectingUsingColorModel(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h);
	//ref:Visitor Identification Elaborating Real Time Face Recognition System
	void static detectingUsing2ndColorModel(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h);
	//ref FACE LOCALIZATION AND FACIAL FEATURE EXTRACTION BASED ON SHAPE AND COLOR INFORMATION 
	void static detectingUsing3thColorModel(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h);
	void static detectingUsing4thColorModel(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h);
	void static detectingUsingClusters(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h);
	void static detectingUsingGrabcut(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h);
	static CascadeClassifier faceCascade;
};
#endif
