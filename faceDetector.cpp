#include "faceDetector.h"
//attention:only 2nd color model works
CascadeClassifier faceDetector::faceCascade;
void faceDetector::detectingFace(Mat &srcMat,Mat &faceMask,unsigned char mode,Rect &face)
{
	int x=face.x,y=face.y,w=face.width,h=face.height;
	if(mode&FACE_USINGOPENCV)
	{
		face=detectingFacesUsingOpencv(srcMat);
		x=face.x;
		y=face.y;
		w=face.width;
		h=face.height;
	}
	if(mode&FACE_COLORMODEL)
	{
		detectingUsing2ndColorModel(srcMat,faceMask,x,y,w,h);
	}
	if(mode&FACE_USING_CLUSTER)
	{
		//detectingUsingClusters(srcMat,faceMask,x,y,w,h);
		detectingUsingGrabcut(srcMat,faceMask,x,y,w,h);
	}
}
void faceDetector::detectingUsing4thColorModel(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h)
{
	double R,G,B,Y,Cb,Cr,x1,y1,value;
	for(int i=x;i<w;++i)
		for(int j=y;j<h;++j)
		{
			B=(double)srcMat.at<Vec3b>(j,i)[0];
			G=(double)srcMat.at<Vec3b>(j,i)[1];
			R=(double)srcMat.at<Vec3b>(j,i)[2];
			Cb=0.5*B+128-0.1687*R-0.3313*G;
			Cr=0.5*R-0.4187*G-0.0813*B+128;
			Y=0.299*R+0.587*G+0.114*B;
			Cb-=109;
			Cr-=152;
			x1 = (819*Cr-614*Cb)/32 + 51;  
			y1 = (819*Cr+614*Cb)/32 + 77;  
			x1 = x1*41/1024;  
			y1 = y1*73/1024;  
			value=x1*x1+y1*y1;
			if(faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE)
			{
				if(!((Y<100&&value<700)||(Y>100&&value<850)))
					faceMask.at<uchar>(j,i)=NOTFACE_PIXEL_VALUE;
			}
		}
}
void faceDetector::loadCascade()
{
	string faceCascadeString="haarcascade_frontalface_alt2.xml";
	faceCascade.load(faceCascadeString);
}
void faceDetector::detectingUsing3thColorModel(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h)
{
	Mat hsvMat(srcMat.rows,srcMat.cols,CV_32FC3);
	ColorSpaceTransition::rgb2Hsv(srcMat,hsvMat);
	float H,S;
	for(int i=x;i<w;++i)
		for(int j=y;j<h;++j)
		{
			H=hsvMat.at<Vec3f>(j,i)[2];
			S=hsvMat.at<Vec3f>(j,i)[1];
			if(!(H>=0&&H<=50&&S>=0.23&&S<=0.68&&faceMask.at<uchar>(j,i)==FACE_PIXEL_VALUE))
				faceMask.at<uchar>(j,i)=NOTFACE_PIXEL_VALUE;
		}
	//detectingUsing4thColorModel(srcMat,faceMask,x,y,w,h);
}
void faceDetector::detectingUsing2ndColorModel(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h)
{
	double R,G,B,Cb,Cr;
	for(int i=x;i<w+x;++i)
		for(int j=y;j<h+y;++j)
		{
			B=(double)srcMat.at<Vec3b>(j,i)[0];
			G=(double)srcMat.at<Vec3b>(j,i)[1];
			R=(double)srcMat.at<Vec3b>(j,i)[2];
			Cb=0.5*B+128-0.1687*R-0.3313*G;
			Cr=0.5*R-0.4187*G-0.0813*B+128;
			Cb=Cb>255?255:Cb;
			Cb=Cb<0?0:Cb;
			Cr=Cr>255?255:Cr;
			Cr=Cr<0?0:Cr;
			//ref:Locating Facial Region of a Head-and-Shoulders Color Image
			if(Cr>=133&&Cr<=173&&Cb>=77&&Cb<=127)
				faceMask.at<uchar>(j,i)=FACE_PIXEL_VALUE;
		}
	//detectingUsing3thColorModel(srcMat,faceMask,x,y,w,h);
}
//discard!
void faceDetector::detectingUsingColorModel(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h)
{
	double R,G,B,Cb,Cr,x1,x2,t,p,pixelscales=0,thd;
	double *prob=new double[w*h],*tempProb=new double[w*h];
	for(int i=x;i<w;++i)
		for(int j=y;j<h;++j)
		{
			B=(double)srcMat.at<Vec3b>(j,i)[0];
			G=(double)srcMat.at<Vec3b>(j,i)[1];
			R=(double)srcMat.at<Vec3b>(j,i)[2];
			Cb=(128 - 37.797 * R/255.0 - 74.203 * G/255.0 +   112 * B/255.0);
			Cr=(128 + 112    * R/255.0 - 93.786 * G/255.0 -18.214 * B/255.0);
			x1=Cb-colorModelCbMean;
			x2=Cr-colorModelCrMean;
			t=x1*(x1*colorModelCov11-x2*colorModelCov10)+x2*(x2*colorModelCov00-x1*colorModelCov01);
			t=-0.5*t/(colorModelCov00*colorModelCov11-colorModelCov01*colorModelCov10);
			p=exp(t);
			prob[j*w+i]=p;
			pixelscales+=p;
		}
	memcpy(tempProb,prob,sizeof(double)*w*h);
	for(int i=4;i<h-4;++i)
		for(int j=4;j<w-4;++j)
		{
			prob[i*w+j]=0;
			for(int m=-4;m<=4;++m)
				for(int n=-4;n<=4;++n)
				{
					prob[i*w+j]+=tempProb[(i+m)*w+j+n];
				}
			prob[i*w+j]/=81;
		}
	thd=pixelscales/(w*h);
	for(int i=x;i<w;++i)
		for(int j=y;j<h;++j)
		{
			if(prob[j*w+i]<thd)
				faceMask.at<uchar>(j,i)=NOTFACE_PIXEL_VALUE;
			else
				faceMask.at<uchar>(j,i)=FACE_PIXEL_VALUE;
		}
		detectingUsing2ndColorModel(srcMat,faceMask,x,y,w,h);
		delete [] prob;
		delete [] tempProb;
}
Rect faceDetector::detectingFacesUsingOpencv(Mat &srcMat)
{
	cv::Mat gray;
	cvtColor(srcMat,gray,CV_BGR2GRAY);
	equalizeHist(gray,gray);
	vector<Rect> faces;
	faceCascade.detectMultiScale(gray,faces,1.1,2,CV_HAAR_SCALE_IMAGE,Size(30,30));
	if(faces.empty())
		return Rect(0,0,srcMat.cols,srcMat.rows);
	int minx=faces[0].x,miny=faces[0].y,maxw=faces[0].width+faces[0].x,maxh=faces[0].height+faces[0].y;
	for(int i=1;i<faces.size();++i)
	{
		minx=(minx>faces[i].x)?faces[i].x:minx;
		miny=(miny>faces[i].y)?faces[i].y:miny;
		maxw=(maxw>(faces[i].width+faces[i].x))?maxw:(faces[i].width+faces[i].x);
		maxh=(maxh>(faces[i].height+faces[i].y))?maxh:(faces[i].height+faces[i].y);
	}
	return Rect(minx,miny,maxw-minx,maxh-miny);
}
void faceDetector::detectingUsingClusters(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h)
{
	Mat samples=Mat::zeros(w*h,2,CV_32F);
	Mat clusers;
	int k=0;
	float R,G,B,Cb,Cr;
	for(int i=y;i<h+y;++i)
		for(int j=x;j<w+x;++j,++k)
		{
			B=(double)srcMat.at<Vec3b>(i,j)[0];
			G=(double)srcMat.at<Vec3b>(i,j)[1];
			R=(double)srcMat.at<Vec3b>(i,j)[2];
			Cb=0.5*B+128-0.1687*R-0.3313*G;
			Cr=0.5*R-0.4187*G-0.0813*B+128;
			Cb=Cb>255?255:Cb;
			Cb=Cb<0?0:Cb;
			Cr=Cr>255?255:Cr;
			Cr=Cr<0?0:Cr;
			samples.at<float>(k,0)=Cb;
			samples.at<float>(k,1)=Cr;
			//samples.at<float>(k,3)=(float)(j-x-(w>>1));
			//samples.at<float>(k,4)=(float)(i-y-(h>>1));//symmetry
		}
	int nClusters=3;
	kmeans(samples,nClusters,clusers,TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,10,1.0),2,KMEANS_PP_CENTERS);
#ifdef DEBUG
	k=0;
	Mat result=Mat::zeros(h,w,CV_8UC1);
	float step=255.0/(nClusters-1);
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j,++k)
		{
			result.at<uchar>(i,j)=clusers.at<int>(k,0)*step;
		}
	imwrite("hello.jpg",result);
#endif
	vector<int> pixelCount(nClusters,0);
	k=0;
	for(int i=y;i<h+y;++i)
		for(int j=x;j<w+x;++j,++k)
		{
			if(faceMask.at<uchar>(i,j)==FACE_PIXEL_VALUE)
			{
				pixelCount[clusers.at<int>(k,0)]++;
			}
		}
	int pixelNumberMax=pixelCount[0],index=0;
	for(int i=1;i<nClusters;++i)
	{
		if(pixelCount[i]>pixelNumberMax)
		{
			pixelNumberMax=pixelCount[i];
			index=i;
		}
	}
	k=0;
	for(int i=y;i<h+y;++i)
		for(int j=x;j<w+x;++j,++k)
		{
			if(faceMask.at<uchar>(i,j)==FACE_PIXEL_VALUE&&clusers.at<int>(k,0)!=index)
				faceMask.at<uchar>(i,j)=NOTFACE_PIXEL_VALUE;
		}
}
void faceDetector::detectingUsingGrabcut(Mat &srcMat,Mat &faceMask,int x,int y,int w,int h)
{
	Mat grabCutMask(srcMat.rows,srcMat.cols,CV_8UC1);
	for(int i=y;i<h+y;++i)
		for(int j=x;j<w+x;++j)
		{
			if(faceMask.at<uchar>(i,j)==FACE_PIXEL_VALUE)
				grabCutMask.at<uchar>(i,j)=GC_FGD;
			else
				grabCutMask.at<uchar>(i,j)=GC_PR_FGD;
		}
	grabCut(srcMat,grabCutMask,Rect(x,y,w,h),Mat(),Mat(),1,GC_INIT_WITH_RECT);
	for(int i=y;i<h+y;++i)
		for(int j=x;j<w+x;++j)
		{
			if(grabCutMask.at<uchar>(i,j)==GC_FGD||grabCutMask.at<uchar>(i,j)==GC_PR_FGD)
				faceMask.at<uchar>(i,j)=FACE_PIXEL_VALUE;
			else
				faceMask.at<uchar>(i,j)=NOTFACE_PIXEL_VALUE;
		}
}