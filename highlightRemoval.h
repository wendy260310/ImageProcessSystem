#ifndef _HIGHLIGHT_REMOVAL_H
#define _HIGHLIGHT_REMOVAL_H
#include "parameters.h"
#include "header.h"
#include "MinNHeap.h"
#include "PatchSparsity.h"
#include "ColorSpaceTransitionClass.h"
#ifdef ENABELLOG
#include <fstream>
#endif
class PossionMethodThread:public QThread
{
public:
	PossionMethodThread(Mat &_srcMat,Mat &_resultMat,Mat &_highlightMask,int _channel,int *_position,int _pixelNumber,Rect &_face);
protected:
	void run();
private:
	int channel,*position,pixelNumber;
	Mat &srcMat,&highlightMask,&resultMat;
	Rect &face;
};
//ref:Image Inpainting by Patch Propagation Using Patch Sparsity
class ImageInpaintingMethod
{
public:
	static void removal(Mat &srcMat,Mat &resultMat,Mat &highlightMask,Rect &face);
private:
	static double patchSparsity(Mat &srcMat,Mat &fillRegion,int x,int y,vector<double> &weight);
	static bool patchBelongsToKnownArea(Mat &fillRegion,int x,int y);
	static double patchMeanSquaredDistance(Mat &srcMat,Mat &fillRegion,int x1,int y1,int x2,int y2,unsigned char pixelValue);
	static double patchSSDError(Mat &srcMat,Mat &fillRegion,int x1,int y1,int x2,int y2,unsigned char pixelValue);
	static double patchConfidence(Mat &fillRegion,Mat &confidence,int x,int y,unsigned char pixelValue);
	static void siglePathBestMatch(int inpaintX,int inpaintY,Mat &fillRegion,int &bestMatchX,int &bestMatchY,Rect &face,Mat &srcMat);
	static void initPatchSparsity(Mat &srcMat,Mat &fillRegion,Rect &face,list< PatchSparsity *> &patchList,multimap<int,list< PatchSparsity *>::iterator > &key);
	static void updateSparsityList(Mat &srcMat,Mat &fillRegion,list< PatchSparsity *> &patchList,multimap<int,list< PatchSparsity *>::iterator> &key,int x,int y);
	static void insertPatchSparsityIntoList(Mat &srcMat,Mat &fillRegion,list< PatchSparsity *> &patchList,multimap<int,list< PatchSparsity *>::iterator> &key,int x,int y);
#ifdef ENABELLOG
	static fstream output;
#endif
};
class HighLightRemoval
{
public:
	void static removal(Mat &srcMat,Mat &resultMat,Mat &highlightMask,Rect &face,unsigned char mode);
};
#endif