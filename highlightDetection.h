#ifndef _HIGHLIGHT_DETECTION_
#define _HIGHLIGHT_DETECTION_
#include "parameters.h"
#include "header.h"
#include "ColorSpaceTransitionClass.h"
#include "BasisOperation.h"
class HighLightDetection
{
public:
	void static highlightDetection(Mat &highlightMask,Mat &srcMat,Mat &faceMask,unsigned char mode,Rect &r);
private:
	//ref to Automatic Detection and Correction for Glossy Reflections in Digital Photograph
	void static glossyReflectionMethod(Mat &highlightMask,Mat &srcMat,Mat &faceMask);

	void static valueAndSaturation(Mat &highlightMask,Mat &srcMat,Mat &faceMask,Rect &r);

	void static localGradient(Mat &highlightMask,Mat &srcMat,Mat &faceMask,Rect &r);
};
#endif