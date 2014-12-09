#include "BasisOperation.h"
#include "parameters.h"
double BasisOperation::gradient(Mat &srcMat,int x,int y,int channel,unsigned char orientation,unsigned char mode)
{
	int x1Offset=0,y1Offset=0,x2Offset=0,y2Offset=0;
	double ratio;
	if(orientation&GRADIENT_ORIENTATION_HORIZONTAL)
	{
		x2Offset=-1;
		x1Offset=(mode&GRADIENT_MATLAB)?1:0;
		ratio=(mode&GRADIENT_MATLAB)?0.5:1;
	}
	if(orientation&GRADIENT_ORIENTATION_VERTICAL)
	{
		y2Offset=-1;
		y1Offset=(mode&GRADIENT_MATLAB)?1:0;
		ratio=(mode&GRADIENT_MATLAB)?0.5:1;
	}
	double result=((double)srcMat.at<Vec3b>(y+y1Offset,x+x1Offset)[channel]-(double)srcMat.at<Vec3b>(y+y2Offset,x+x2Offset)[channel])*ratio;
	return result;
}
void BasisOperation::mat2QImage(Mat &mat,QImage &img)
{
	int w=mat.cols,h=mat.rows;
	unsigned char *matPtr=mat.data;
	unsigned char *imgPtr=(unsigned char *)img.bits();
	for(int i=0;i<w*h;++i)
	{
		imgPtr[2]=matPtr[2];
		imgPtr[1]=matPtr[1];
		imgPtr[0]=matPtr[0];
		imgPtr+=4;
		matPtr+=3;
	}
}
//here mapping function y=a*x*x+b*x;control point (red,0.5),(green,0.5),(blue,0.5)
void BasisOperation::ColorBalance(Mat &srcMat,Mat &result,double red,double green,double blue)
{
	double tempRed,tempGreen,tempBlue;
	uchar  red_lookup_table[256],green_lookup_table[256],blue_lookup_table[256];
	double x,y,red_a,red_b,green_a,green_b,blue_a,blue_b;
	red_a=(red-0.5)/(0.5*0.5-0.5);
	red_b=1-red_a;
	green_a=(green-0.5)/(0.5*0.5-0.5);
	green_b=1-green_a;
	blue_a=(blue-0.5)/(0.5*0.5-0.5);
	blue_b=1-blue_a;
	for(unsigned int i=0;i<256;++i)
	{
		x=i/255.0;
		y=red_a*x*x+red_b*x;
		y=y<0?0:y;
		y=y>1?1:y;
		red_lookup_table[i]=(unsigned char)(y*255);
		y=green_a*x*x+green_b*x;
		y=y<0?0:y;
		y=y>1?1:y;
		green_lookup_table[i]=(unsigned char)(y*255);
		y=blue_a*x*x+blue_b*x;
		y=y<0?0:y;
		y=y>1?1:y;
		blue_lookup_table[i]=(unsigned char)(y*255);
	}
	for(unsigned int i=0;i<srcMat.rows;++i)
		for(unsigned int j=0;j<srcMat.cols;++j)
		{
			result.at<Vec3b>(i,j)[2]=red_lookup_table[srcMat.at<Vec3b>(i,j)[2]];
			result.at<Vec3b>(i,j)[1]=green_lookup_table[srcMat.at<Vec3b>(i,j)[1]];
			result.at<Vec3b>(i,j)[0]=blue_lookup_table[srcMat.at<Vec3b>(i,j)[0]];
		}
}
void BasisOperation::qimage2Mat(QImage &img,Mat &mat)
{
	int w=img.width(),h=img.height();
	const unsigned char *imgPtr=(unsigned char *)img.constBits();
	unsigned char *matPtr=mat.data;
	for(int i=0;i<w*h;++i)
	{
		matPtr[2]=imgPtr[2];
		matPtr[1]=imgPtr[1];
		matPtr[0]=imgPtr[0];
		matPtr+=3;
		imgPtr+=4;
	}
}
void BasisOperation::sharpEffect(Mat &srcMat,Mat &resultMat)
{
	Mat kernel=(Mat_<float>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);
	filter2D(srcMat,resultMat,srcMat.depth(),kernel);
}
void BasisOperation::regionExtraction(Mat *srcMat,Mat *regionMask,int threhold,Rect &region,int startX,int startY)
{
	queue<QPoint> pixelQueue;
	int maxX=-1,maxY=-1,minX=srcMat->cols+1,minY=srcMat->rows+1;
	int w=srcMat->cols,h=srcMat->rows;
	unsigned char *visited=new unsigned char[srcMat->rows*srcMat->cols];
	memset(visited,0,sizeof(unsigned char)*srcMat->rows*srcMat->cols);
	QPoint temp(startX,startY);
	pixelQueue.push(temp);
	regionMask->at<uchar>(startY,startX)=PIXEL_SELECTED_VALUE;
	visited[startY*w+startX]=1;
	while(!pixelQueue.empty())
	{
		temp=pixelQueue.front();
		pixelQueue.pop();
		int x=temp.x(),y=temp.y();
		bool boundary=false;
		if(y!=0&&x!=0&&!visited[(y-1)*w+x-1])
		{
			visited[(y-1)*w+x-1]=1;
			if(!insertIntoQueue(srcMat,regionMask,threhold,startX,startY,x-1,y-1,pixelQueue))
			{
				if(!boundary)
				{
					maxX=x>maxX?x:maxX;
					maxY=y>maxY?y:maxY;
					minX=x<minX?x:minX;
					minY=y<minY?y:minY;
					boundary=true;
				}
			}
		}
		if(y!=0&&!visited[(y-1)*w+x])
		{
			visited[(y-1)*w+x]=1;
			if(!insertIntoQueue(srcMat,regionMask,threhold,startX,startY,x,y-1,pixelQueue))
			{
				if(!boundary)
				{
					maxX=x>maxX?x:maxX;
					maxY=y>maxY?y:maxY;
					minX=x<minX?x:minX;
					minY=y<minY?y:minY;
					boundary=true;
				}
			}
		}
		if(y!=0&&(x!=w-1)&&!visited[(y-1)*w+x+1])
		{
			visited[(y-1)*w+x+1]=1;
			if(!insertIntoQueue(srcMat,regionMask,threhold,startX,startY,x+1,y-1,pixelQueue))
			{
				if(!boundary)
				{
					maxX=x>maxX?x:maxX;
					maxY=y>maxY?y:maxY;
					minX=x<minX?x:minX;
					minY=y<minY?y:minY;
					boundary=true;
				}
			}
		}
		if(x!=0&&!visited[y*w+x-1])
		{
			visited[y*w+x-1]=1;
			if(!insertIntoQueue(srcMat,regionMask,threhold,startX,startY,x-1,y,pixelQueue))
			{
				if(!boundary)
				{
					maxX=x>maxX?x:maxX;
					maxY=y>maxY?y:maxY;
					minX=x<minX?x:minX;
					minY=y<minY?y:minY;
					boundary=true;
				}
			}
		}
		if((x!=w-1)&&!visited[y*w+x+1])
		{
			visited[y*w+x+1]=1;
			if(!insertIntoQueue(srcMat,regionMask,threhold,startX,startY,x+1,y,pixelQueue))
			{
				if(!boundary)
				{
					maxX=x>maxX?x:maxX;
					maxY=y>maxY?y:maxY;
					minX=x<minX?x:minX;
					minY=y<minY?y:minY;
					boundary=true;
				}
			}
		}
		if((y!=h-1)&&x!=0&&!visited[(y+1)*w+x-1])
		{
			visited[(y+1)*w+x-1]=1;
			if(!insertIntoQueue(srcMat,regionMask,threhold,startX,startY,x-1,y+1,pixelQueue))
			{
				if(!boundary)
				{
					maxX=x>maxX?x:maxX;
					maxY=y>maxY?y:maxY;
					minX=x<minX?x:minX;
					minY=y<minY?y:minY;
					boundary=true;
				}
			}
		}
		if((y!=h-1)&&!visited[(y+1)*w+x])
		{
			visited[(y+1)*w+x]=1;
			if(!insertIntoQueue(srcMat,regionMask,threhold,startX,startY,x,y+1,pixelQueue))
			{
				if(!boundary)
				{
					maxX=x>maxX?x:maxX;
					maxY=y>maxY?y:maxY;
					minX=x<minX?x:minX;
					minY=y<minY?y:minY;
					boundary=true;
				}
			}
		}
		if((y!=h-1)&&(x!=w-1)&&!visited[(y+1)*w+x+1])
		{
			visited[(y+1)*w+x+1]=1;
			if(!insertIntoQueue(srcMat,regionMask,threhold,startX,startY,x+1,y+1,pixelQueue))
			{
				if(!boundary)
				{
					maxX=x>maxX?x:maxX;
					maxY=y>maxY?y:maxY;
					minX=x<minX?x:minX;
					minY=y<minY?y:minY;
					boundary=true;
				}
			}
		}
	}
	region.x=minX;
	region.y=minY;
	region.width=maxX-minX;
	region.height=maxY-minY;
}
//this method is used for regionExtraction
bool BasisOperation::insertIntoQueue(Mat *srcMat,Mat * regionMask,int threhold,int x1,int y1,int x2,int y2,queue<QPoint> &pixelQueue)
{
	int maxChannelDifference=-256,minChannelDifference=256;
	int difference=0;
	int R=abs((int)srcMat->at<Vec3b>(y1,x1)[2]-(int)srcMat->at<Vec3b>(y2,x2)[2]);
	int G=abs((int)srcMat->at<Vec3b>(y1,x1)[1]-(int)srcMat->at<Vec3b>(y2,x2)[1]);
	int B=abs((int)srcMat->at<Vec3b>(y1,x1)[0]-(int)srcMat->at<Vec3b>(y2,x2)[0]);
	difference=((R>G?R:G)>B)?(R>G?R:G):B;
	if(difference<=threhold)
	{
		QPoint p(x2,y2);
		regionMask->at<uchar>(y2,x2)=PIXEL_SELECTED_VALUE;
		pixelQueue.push(p);
		return true;
	}
	return false;
}
bool BasisOperation::pixelIsBoundary(Mat &img,int x,int y)
{
	if(x==0||(x==img.cols-1)||y==0||(y==img.rows-1))
		return true;
	return (8*(int)img.at<uchar>(y,x)-(int)img.at<uchar>(y-1,x-1)-(int)img.at<uchar>(y-1,x)-(int)img.at<uchar>(y-1,x+1)-(int)img.at<uchar>(y,x-1)-(int)img.at<uchar>(y,x+1)-(int)img.at<uchar>(y+1,x-1)-(int)img.at<uchar>(y+1,x)-(int)img.at<uchar>(y+1,x+1))>0;
}
void BasisOperation::localEnhencementUsingMappingMethod(Mat &resultMat,Mat *mask,double x,double y,int channal)
{
	int w=resultMat.cols,h=resultMat.rows;
	double pixelValue,outputValue;
#ifdef VALUE_COMBINE
	double a,b,weight;
	a=(y-x)/(x*x-x);
	b=(x*x-y)/(x*x-x);
#else
	double a,b,combineY,weight;
#endif
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			if(mask->at<uchar>(j,i)!=PIXEL_NOT_SELECTED_VALUE)
			{
				weight=mask->at<uchar>(j,i)/255.0;
				pixelValue=resultMat.at<Vec3b>(j,i)[channal]/255.0;
#ifdef VALUE_COMBINE
				outputValue=a*pixelValue*pixelValue+b*pixelValue;
				outputValue=(weight*outputValue+(1-weight)*pixelValue)*255;
#else
				combineY=y*weight+(1-weight)*0.5;
				a=(combineY-x)/(x*x-x);
				b=(x*x-combineY)/(x*x-x);
				outputValue=(a*pixelValue*pixelValue+b*pixelValue)*255;
#endif
				outputValue=outputValue>255?255:outputValue;
				outputValue=outputValue<0?0:outputValue;
				resultMat.at<Vec3b>(j,i)[channal]=(uchar)outputValue;
			}
		}
}
void BasisOperation::localEnhencementUsingMappingMethod(Mat &resultMat,Mat * mask,double x,double y)
{
	localEnhencementUsingMappingMethod(resultMat,mask,x,y,0);
	localEnhencementUsingMappingMethod(resultMat,mask,x,y,1);
	localEnhencementUsingMappingMethod(resultMat,mask,x,y,2);
}
bool BasisOperation::faceNeedColorCorrection(Mat &srcMat,Mat &faceMask,Rect &face)
{
	int x=face.x,y=face.y,w=face.width,h=face.height;
	int pixelNumber=0;
	double rSum=0,gSum=0,bSum=0;
	for(int i=x;i<w+x;++i)
		for(int j=y;j<h+y;++j)
		{
			if(faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE)
			{
				pixelNumber++;
				rSum+=srcMat.at<Vec3b>(j,i)[2];
				gSum+=srcMat.at<Vec3b>(j,i)[1];
				bSum+=srcMat.at<Vec3b>(j,i)[0];
			}
		}
		rSum/=pixelNumber;
		gSum/=pixelNumber;
		bSum/=pixelNumber;
	double data1=rSum*100/gSum;
	double data2=rSum*100/bSum;
	double data3=data2-data1;
	double data4=gSum*100/bSum;
	double brightness=0.3*rSum+0.59*gSum+0.11*bSum;
	if(data1>=129||data1<=116)
		return true;
	if(data4<=103)
		return true;
	if(data3>=14&&data4>=116)
		return true;
	if(brightness<170||brightness>190)
		return true;
	return false;
}
//ref Ostu method
double BasisOperation::thresholdOstuMethod(Mat &hsvMat,Mat &faceMask,Rect face,int channel)
{
	double bins[100]={0};
	int count=0;
	int x=face.x,y=face.y,w=face.width,h=face.height;
	for(int i=x;i<x+w;++i)
		for(int j=y;j<y+h;++j)
		{
			if(faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE)
			{
				bins[(int)((hsvMat.at<Vec3f>(j,i)[channel]-0.001)*100)]++;
				count++;
			}
		}
	for(int i=0;i<100;++i)
		bins[i]/=count;
	double sigmaB=-1,threshold,tempsigma;
	for(int i=0;i<100;++i)
	{
		double w0=0,w1=0,miu0=0,miu1=0;
		for(int j=0;j<=i;++j)
		{
			w0+=bins[j];
			miu0+=j*bins[j]*0.01;
		}
		miu0/=w0;
		w1=1-w0;
		for(int j=i+1;j<100;++j)
		{
			miu1=j*bins[j]*0.01;
		}
		miu1/=w1;
		tempsigma=w0*w1*(miu1-miu0)*(miu1-miu0);
		if(tempsigma>sigmaB)
		{
			sigmaB=tempsigma;
			threshold=i*0.01;
		}
	}
	return threshold;
}
void BasisOperation::qimage2OneChannelMat(QImage &img,unsigned int imagePixelValue,Mat &mat,unsigned char matPixelValue)
{
	int w=img.width(),h=img.height();
	const unsigned int *imgPtr=(unsigned int *)img.constBits();
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(*imgPtr==imagePixelValue)
				mat.at<uchar>(i,j)=matPixelValue;
			++imgPtr;
		}
}
void BasisOperation::colorLevel(Mat &srcMat,Mat &resultMat,unsigned char low,unsigned char high,int channel,unsigned char mid)
{
	int w=srcMat.cols,h=srcMat.rows;
	double pixelValue;
	unsigned char mappingTable[256]={0};
	for(unsigned int i=low;i<=high;++i)
	{
		mappingTable[i]=getColorLevelValue(low,high,mid,i);
	}
	memset(mappingTable+high,0xff,255-high+1);
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			resultMat.at<Vec3b>(j,i)[channel]=mappingTable[srcMat.at<Vec3b>(j,i)[channel]];
		}
}
unsigned char BasisOperation::getColorLevelValue(unsigned char low,unsigned char high,unsigned char mid,unsigned char pixelValue)
{
	double x=(pixelValue<=mid)?((double)(pixelValue-low)/(mid-low)):((double)(pixelValue-mid)/(high-mid));
	double result=x*127;
	result=(pixelValue<=mid)?result:result+127;
	result=result>255?255:result;
	result=result<0?0:result;
	return (unsigned char)result;
}
void BasisOperation::colorLevel(Mat &srcMat,Mat &resultMat,unsigned char low,unsigned char high,unsigned char mid)
{
	colorLevel(srcMat,resultMat,low,high,0,mid);
	colorLevel(srcMat,resultMat,low,high,1,mid);
	colorLevel(srcMat,resultMat,low,high,2,mid);
}
void BasisOperation::adjustBrightness(Mat &srcMat,Mat &resultMat,Mat &faceMask,int brightnessMeans)
{

}
void BasisOperation::getLowAndHigh(Mat &srcMat,unsigned char &low,unsigned char &high)
{
	unsigned int hisRChannel[256]={0},hisGChannel[256]={0},hisBChannel[256]={0};
	int w=srcMat.cols,h=srcMat.rows;
	low=0;
	high=255;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			hisBChannel[srcMat.at<Vec3b>(j,i)[0]]++;
			hisGChannel[srcMat.at<Vec3b>(j,i)[1]]++;
			hisRChannel[srcMat.at<Vec3b>(j,i)[2]]++;
		}
		for(unsigned int i=0;i<256;++i)
		{
			if((hisRChannel[i]+hisGChannel[i]+hisBChannel[i])>0)
			{
				low=i;
				break;
			}
		}
		for(unsigned int i=255;i>=0;--i)
		{
			if((hisBChannel[i]+hisGChannel[i]+hisRChannel[i])>0)
			{
				high=i;
				break;
			}
		}
}
unsigned char BasisOperation::grayLevel(Mat &srcMat,Mat &faceMask,Rect &face,unsigned char &low,unsigned char &high)
{
	int x=face.x,y=face.y,w=face.width,h=face.height;
	unsigned int hisRChannel[256]={0},hisGChannel[256]={0},hisBChannel[256]={0};
	unsigned int facePixelNumber=0;
	for(unsigned int i=x;i<x+w;++i)
		for(unsigned int j=y;j<y+h;++j)
		{
			if(faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE)
			{
				hisBChannel[srcMat.at<Vec3b>(j,i)[0]]++;
				hisGChannel[srcMat.at<Vec3b>(j,i)[1]]++;
				hisRChannel[srcMat.at<Vec3b>(j,i)[2]]++;
				facePixelNumber++;
			}
		}
	getLowAndHigh(srcMat,low,high);
	unsigned int mid,start=low,end=high;
	double rSum=0,gSum=0,bSum=0;
	while(start<end)
	{
		rSum=0;
		gSum=0;
		bSum=0;
		mid=((end-start)>>1)+start;
		for(unsigned int i=0;i<=mid;++i)
		{
			rSum+=hisRChannel[i]*((i-low)*127.0/(mid-low));
			gSum+=hisGChannel[i]*((i-low)*127.0/(mid-low));
			bSum+=hisBChannel[i]*((i-low)*127.0/(mid-low));
		}
		for(unsigned int i=mid+1;i<=high;++i)
		{
			rSum+=hisRChannel[i]*((i-mid)*127.0/(high-mid)+127);
			gSum+=hisGChannel[i]*((i-mid)*127.0/(high-mid)+127);
			bSum+=hisBChannel[i]*((i-mid)*127.0/(high-mid)+127);
		}
		rSum/=facePixelNumber;
		gSum/=facePixelNumber;
		bSum/=facePixelNumber;
		double brightness=0.3*rSum+0.59*gSum+0.11*bSum;
		if(brightness<150)
			end=mid-1;
		else
			if(brightness<160)
				return mid;
		else
			start=mid+1;
	}
	return start;
}
void BasisOperation::modifySaturationOrLightness(Mat &hsvMat,int channel,float diff)
{
	int w=hsvMat.cols,h=hsvMat.rows;
	float pixelValue;
	for(unsigned int i=0;i<h;++i)
		for(unsigned int j=0;j<w;++j)
		{
			pixelValue=hsvMat.at<Vec3f>(i,j)[channel];
			pixelValue+=diff;
			pixelValue=pixelValue<0?0:pixelValue;
			pixelValue=pixelValue>1?1:pixelValue;
			hsvMat.at<Vec3f>(i,j)[channel]=pixelValue;
		}
}
bool BasisOperation::regionNeedAdjust(Mat &srcMat,Mat &resultMat,int x1,int y1,int x2,int y2,int gridWidth,Rect &face,Mat &faceMask,int *labels,int labelsWidth,int labelsHeight,const double threshold/* =0.2 */)
{
	int label1=labels[y1*labelsWidth+x1],label2=labels[y2*labelsWidth+x2];
	double means[2],pixelNumber[2];
	Mat regionMask[2];
	regionMask[0]=Mat::zeros(srcMat.rows,srcMat.cols,CV_8UC1);
	regionMask[1]=Mat::zeros(srcMat.rows,srcMat.cols,CV_8UC1);
	int lightnessHis[512];
	if((!regionStatistics(srcMat,x1,y1,gridWidth,labels,labelsWidth,labelsHeight,label1,face,faceMask,means[0],pixelNumber[0],regionMask[0],lightnessHis))||(!regionStatistics(srcMat,x2,y2,gridWidth,labels,labelsWidth,labelsHeight,label2,face,faceMask,means[1],pixelNumber[1],regionMask[1],lightnessHis+256)))
		return false;
	if(fabs(means[1]-means[0])>threshold*means[1])
	{
#ifdef DISPLAY_SUPERPIXEL_AND_SYMMETRY
#else
		int index=means[0]<means[1]?0:1;
		double coefficient1=0,coefficient2=pixelNumber[index]*means[1-index]/255.0;
		for(int i=0;i<256;++i)
		{
			double x=i/255.0;
			coefficient1+=x*(x-1)*lightnessHis[index*256+i];
			coefficient2-=x*lightnessHis[index*256+i];
		}
		double a=coefficient2/coefficient1;
		blur(regionMask[index],regionMask[index],Size(21,21));
		BasisOperation::localEnhencementUsingMappingMethod(resultMat,&regionMask[index],0.5,a*0.25+(1-a)*0.5);
#endif
		return true;
	}
	return false;
}
bool BasisOperation::regionStatistics(Mat &srcMat,int x,int y,int gridWidth,int *labels,int labelsWidth,int labelsHeight,int centerLabel,Rect &face,Mat &faceMask,double &mean,double &pixelNumber,Mat &regionMask,int *lightnessHis)
{
	memset(lightnessHis,0,sizeof(int)*256);
	int xLeftBoundary=(x-gridWidth)<0?0:(x-gridWidth),xRightBoundary=(x+gridWidth)>labelsWidth?labelsWidth:(x+gridWidth);
	int yLeftBoundary=(y-gridWidth)<0?0:(y-gridWidth),yRightBoundary=(y+gridWidth)>labelsHeight?labelsHeight:(y+gridWidth);
	pixelNumber=0;
	int totalNumber=0;
	double lightness;
	mean=0;
	for(int i=xLeftBoundary;i<xRightBoundary;++i)
		for(int j=yLeftBoundary;j<yRightBoundary;++j)
		{
			if(labels[j*labelsWidth+i]==centerLabel)
			{
				totalNumber++;
				if(faceMask.at<uchar>(face.y+j,face.x+i)==FACE_PIXEL_VALUE)
				{
					pixelNumber++;
					lightness=srcMat.at<Vec3b>(face.y+j,face.x+i)[2]*0.3+srcMat.at<Vec3b>(face.y+j,face.x+i)[1]*0.59+srcMat.at<Vec3b>(face.y+j,face.x+i)[0]*0.11;
					mean+=lightness;
					lightnessHis[(int)lightness]++;
				}
				regionMask.at<uchar>(face.y+j,face.x+i)=PIXEL_SELECTED_VALUE;
			}
		}
	if(pixelNumber<totalNumber*0.5)
		return false;
	mean=mean/pixelNumber;
	return true;
}
void BasisOperation::regionColorTransfer(Mat &srcMat,Mat &targetMat,Mat &resultMat,Mat &srcRegionMask,Mat &targetRegionMask)
{
	const int bins=1000;
	const double firstChannelStep=255.0/bins,secondChannelStep=255.0/bins,thirdChannelStep=100.0/bins;
	int srcPixelNumber=0,targetPixelNumber=0;
	int w=srcMat.cols,h=srcMat.rows;
	double *firstChannelLookUpTable=new double[bins],*secondChannelLookUpTable=new double[bins],* thirdChannelLookUpTable=new double[bins];
	//here Lab  L->2,a->1,b->0
	double srcFirstChannelHis[bins]={0},srcFirstChannelCulHis[bins],srcSecondChannelHis[bins]={0},srcSecondChannelCulHis[bins],srcThirdChannelHis[bins]={0},srcThirdChannelCulHis[bins];
	double tarFirstChannelHis[bins]={0},tarFirstChannelCulHis[bins],tarSecondChannelHis[bins]={0},tarSecondChannelCulHis[bins],tarThirdChannelHis[bins]={0},tarThirdChannelCulHis[bins];
	int index;
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(srcRegionMask.at<uchar>(i,j)==PIXEL_SELECTED_VALUE)
			{
				srcPixelNumber++;
				//index=(int)((srcMat.at<Vec3f>(i,j)[0]+128)/firstChannelStep);
				//index=(index>=bins)?(bins-1):index;
				//srcFirstChannelHis[index]++;
				//index=(int)((srcMat.at<Vec3f>(i,j)[1]+128)/secondChannelStep);
				//index=(index>=bins)?(bins-1):index;
				//srcSecondChannelHis[index]++;
				index=(int)(srcMat.at<Vec3f>(i,j)[2]/thirdChannelStep);
				index=(index>=bins)?(bins-1):index;
				srcThirdChannelHis[index]++;
			}
			if(targetRegionMask.at<uchar>(i,j)==PIXEL_SELECTED_VALUE)
			{
				targetPixelNumber++;
				//index=(int)((targetMat.at<Vec3f>(i,j)[0]+128)/firstChannelStep);
				//index=(index>=bins)?(bins-1):index;
				//tarFirstChannelHis[index]++;
				//index=(int)((targetMat.at<Vec3f>(i,j)[1]+128)/secondChannelStep);
				//index=(index>=bins)?(bins-1):index;
				//tarSecondChannelHis[index]++;
				index=(int)(targetMat.at<Vec3f>(i,j)[2]/thirdChannelStep);
				index=(index>=bins)?(bins-1):index;
				tarThirdChannelHis[index]++;
			}
		}
	for(int i=0;i<bins;++i)
	{
		//srcFirstChannelHis[i]/=srcPixelNumber;
		//srcSecondChannelHis[i]/=srcPixelNumber;
		srcThirdChannelHis[i]/=srcPixelNumber;
		//tarFirstChannelHis[i]/=targetPixelNumber;
		//tarSecondChannelHis[i]/=targetPixelNumber;
		tarThirdChannelHis[i]/=targetPixelNumber;
	}
	//srcFirstChannelCulHis[0]=srcFirstChannelHis[0];
	//srcSecondChannelCulHis[0]=srcSecondChannelHis[0];
	srcThirdChannelCulHis[0]=srcThirdChannelHis[0];
	//tarFirstChannelCulHis[0]=tarFirstChannelHis[0];
	//tarSecondChannelCulHis[0]=tarSecondChannelHis[0];
	tarThirdChannelCulHis[0]=tarThirdChannelHis[0];
	for(int i=1;i<bins;++i)
	{
		//srcFirstChannelCulHis[i]=srcFirstChannelCulHis[i-1]+srcFirstChannelHis[i];
		//srcSecondChannelCulHis[i]=srcSecondChannelCulHis[i-1]+srcSecondChannelHis[i];
		srcThirdChannelCulHis[i]=srcThirdChannelCulHis[i-1]+srcThirdChannelHis[i];
		//tarFirstChannelCulHis[i]=tarFirstChannelCulHis[i-1]+tarFirstChannelHis[i];
		//tarSecondChannelCulHis[i]=tarSecondChannelCulHis[i-1]+tarSecondChannelHis[i];
		tarThirdChannelCulHis[i]=tarThirdChannelCulHis[i-1]+tarThirdChannelHis[i];
	}
	for(int i=0;i<bins;++i)
	{
		//firstChannelLookUpTable[i]=searchCul(tarFirstChannelCulHis,srcFirstChannelCulHis[i],bins)*firstChannelStep-128;
		//firstChannelLookUpTable[i]=firstChannelLookUpTable[i]>127?127:firstChannelLookUpTable[i];
		//firstChannelLookUpTable[i]=firstChannelLookUpTable[i]<-128?-128:firstChannelLookUpTable[i];
		//secondChannelLookUpTable[i]=searchCul(tarSecondChannelCulHis,srcSecondChannelCulHis[i],bins)*secondChannelStep-128;
		//secondChannelLookUpTable[i]=secondChannelLookUpTable[i]>127?127:secondChannelLookUpTable[i];
		//secondChannelLookUpTable[i]=secondChannelLookUpTable[i]<-128?-128:secondChannelLookUpTable[i];
		thirdChannelLookUpTable[i]=searchCul(tarThirdChannelCulHis,srcThirdChannelCulHis[i],bins)*thirdChannelStep;
		thirdChannelLookUpTable[i]=thirdChannelLookUpTable[i]>100?100:thirdChannelLookUpTable[i];
		thirdChannelLookUpTable[i]=thirdChannelLookUpTable[i]<0?0:thirdChannelLookUpTable[i];
	}
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(srcRegionMask.at<uchar>(i,j)==PIXEL_SELECTED_VALUE)
			{
				//index=(int)((srcMat.at<Vec3f>(i,j)[0]+128)/firstChannelStep);
				//index=index>=bins?(bins-1):index;
				//resultMat.at<Vec3f>(i,j)[0]=firstChannelLookUpTable[index];
				//index=(int)(srcMat.at<Vec3f>(i,j)[1]+128)/secondChannelStep;
				//index=index>=bins?(bins-1):index;
				//resultMat.at<Vec3f>(i,j)[1]=secondChannelLookUpTable[index];
				index=(int)(srcMat.at<Vec3f>(i,j)[2]/thirdChannelStep);
				index=index>=bins?(bins-1):index;
				resultMat.at<Vec3f>(i,j)[2]=thirdChannelLookUpTable[index];
			}
		}
	delete []firstChannelLookUpTable;
	delete [] secondChannelLookUpTable;
	delete []thirdChannelLookUpTable;
}
int BasisOperation::searchCul(double *culHis,double value,int bins)
{

	for(int i=1;i<bins;++i)
	{
		if(culHis[i]>value)
		{
			return (culHis[i]-value)>(value-culHis[i-1])?(i-1):i;
		}
	}
	return bins-1;
}
void BasisOperation::poissonEditing(Mat &srcMat,Mat &resultMat,Mat &regionMask,int *position,int regionPixelnumber,int channel,double lowPixelValueBoundary,double highPixelValueBoundary)
{
	SpMat A(regionPixelnumber,regionPixelnumber);
	Eigen::VectorXd x(regionPixelnumber),b(regionPixelnumber);
	A.setZero();
	x.setZero();
	b.setZero();
	vector<T> tripleList;
	int count=0;
	int w=srcMat.cols,h=srcMat.rows;
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(regionMask.at<uchar>(i,j)==PIXEL_SELECTED_VALUE)
			{
				//please pay attention to the region boundary
				tripleList.push_back(T(count,count,4));
				//up
				if(i!=0&&regionMask.at<uchar>(i-1,j)==PIXEL_SELECTED_VALUE)
				{
					tripleList.push_back(T(count,position[(i-1)*w+j],-1));
					b(count)+=(double)srcMat.at<Vec3b>(i,j)[channel]-(double)srcMat.at<Vec3b>(i-1,j)[channel];
				}
				else
					b(count)+=srcMat.at<Vec3b>(i-1,j)[channel];
				//down
				if(i!=(h-1)&&regionMask.at<uchar>(i+1,j)==PIXEL_SELECTED_VALUE)
				{
					tripleList.push_back(T(count,position[(i+1)*w+j],-1));
					b(count)+=(double)srcMat.at<Vec3b>(i,j)[channel]-(double)srcMat.at<Vec3b>(i+1,j)[channel];
				}
				else
					b(count)+=srcMat.at<Vec3b>(i+1,j)[channel];
				//left
				if(j!=0&&regionMask.at<uchar>(i,j-1)==PIXEL_SELECTED_VALUE)
				{
					tripleList.push_back(T(count,position[i*w+j-1],-1));
					b(count)+=(double)srcMat.at<Vec3b>(i,j)[channel]-(double)srcMat.at<Vec3b>(i,j-1)[channel];
				}
					
				else
					b(count)+=srcMat.at<Vec3b>(i,j-1)[channel];
				//right
				if(j!=(w-1)&&regionMask.at<uchar>(i,j+1)==PIXEL_SELECTED_VALUE)
				{
					tripleList.push_back(T(count,position[i*w+j+1],-1));
					b(count)+=(double)srcMat.at<Vec3b>(i,j)[channel]-(double)srcMat.at<Vec3b>(i,j+1)[channel];
				}
				else
					b(count)+=srcMat.at<Vec3b>(i,j+1)[channel];
				//b(count)+=(double)srcMat.at<Vec3f>(i,j)[channel]*4-(double)srcMat.at<Vec3f>(i+1,j)[channel]-(double)srcMat.at<Vec3f>(i-1,j)[channel]-(double)srcMat.at<Vec3f>(i,j-1)[channel]-(double)srcMat.at<Vec3f>(i,j+1)[channel];
				count++;
			}
		}
	A.setFromTriplets(tripleList.begin(),tripleList.end());
	Eigen::SimplicialCholesky< Eigen::SparseMatrix<double> > slu;
	slu.compute(A.transpose()*A);
	x=slu.solve(A.transpose()*b);
	double pixelValue;
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(regionMask.at<uchar>(i,j)==PIXEL_SELECTED_VALUE)
			{
				pixelValue=x(position[i*w+j]);
				pixelValue=pixelValue<lowPixelValueBoundary?lowPixelValueBoundary:pixelValue;
				pixelValue=pixelValue>highPixelValueBoundary?highPixelValueBoundary:pixelValue;
				resultMat.at<Vec3b>(i,j)[channel]=(uchar)pixelValue;
			}
		}
}
void BasisOperation::poissonEditing(Mat &srcMat,Mat &resultMat,Mat &regionMask,int *position,int regionPixelnumber,int channel,int faceImageWidth,Rect r)
{
	SpMat A(regionPixelnumber,regionPixelnumber);
	Eigen::VectorXd x(regionPixelnumber),b(regionPixelnumber);
	A.setZero();
	x.setZero();
	b.setZero();
	vector<T> tripleList;
	int count=0;
	int w=srcMat.cols,h=srcMat.rows;
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(regionMask.at<uchar>(i,j)==PIXEL_SELECTED_VALUE)
			{
				tripleList.push_back(T(count,count,4));
				if(i!=0&&regionMask.at<uchar>(i-1,j)==PIXEL_SELECTED_VALUE)
				{
					tripleList.push_back(T(count,position[(i-1)*w+j],-1));
				}
				else
					b(count)+=srcMat.at<Vec3b>(i-1,j)[channel];
				//down
				if(i!=(h-1)&&regionMask.at<uchar>(i+1,j)==PIXEL_SELECTED_VALUE)
				{
					tripleList.push_back(T(count,position[(i+1)*w+j],-1));
				}
				else
					b(count)+=srcMat.at<Vec3b>(i+1,j)[channel];
				//left
				if(j!=0&&regionMask.at<uchar>(i,j-1)==PIXEL_SELECTED_VALUE)
				{
					tripleList.push_back(T(count,position[i*w+j-1],-1));
				}

				else
					b(count)+=srcMat.at<Vec3b>(i,j-1)[channel];
				//right
				if(j!=(w-1)&&regionMask.at<uchar>(i,j+1)==PIXEL_SELECTED_VALUE)
				{
					tripleList.push_back(T(count,position[i*w+j+1],-1));
				}
				else
					b(count)+=srcMat.at<Vec3b>(i,j+1)[channel];
				b(count)+=(double)srcMat.at<Vec3b>(i,faceImageWidth-1-j+r.x)[channel]*4-(double)srcMat.at<Vec3b>(i+1,faceImageWidth-1-j+r.x)[channel]-(double)srcMat.at<Vec3b>(i-1,faceImageWidth-1-j+r.x)[channel]-(double)srcMat.at<Vec3b>(i,faceImageWidth-1-j+r.x+1)[channel]-(double)srcMat.at<Vec3b>(i,faceImageWidth-1-j+r.x-1)[channel];
				count++;
			}
		}
	A.setFromTriplets(tripleList.begin(),tripleList.end());
	Eigen::SimplicialCholesky< Eigen::SparseMatrix<double> > slu;
	slu.compute(A.transpose()*A);
	x=slu.solve(A.transpose()*b);
	double pixelValue;
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j)
		{
			if(regionMask.at<uchar>(i,j)==PIXEL_SELECTED_VALUE)
			{
				pixelValue=x(position[i*w+j]);
				pixelValue=pixelValue<0?0:pixelValue;
				pixelValue=pixelValue>255?255:pixelValue;
				resultMat.at<Vec3b>(i,j)[channel]=(unsigned char)pixelValue;
			}
		}
}