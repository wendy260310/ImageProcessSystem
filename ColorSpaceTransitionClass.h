#ifndef COLOR_SPACE_TRANSITION_H
#define COLOR_SPACE_TRANSITION_H
#include "parameters.h"
#include "header.h"
class ColorSpaceTransition
{
public:
	void static rgb2Lab(Mat &rgbMat,Mat &labMat);
	void static lab2Rgb(Mat &labMat,Mat &rgbMat);
	void static rgb2Hsv(Mat &rgbMat,Mat &hsvMat);
	void static hsv2Rgb(Mat &hsvMat,Mat &rgbMat);
	//ref:彩色图像人脸高光区域的自动检测与校正方法
	void static rgb2Tsl(Mat &rgbMat,Mat &tslMat);
};
#endif