#include "highlightRemoval.h"
#include "BasisOperation.h"
//discard
#ifdef ENABELLOG
	fstream ImageInpaintingMethod::output("D:\\a.txt");
#endif
PossionMethodThread::PossionMethodThread(Mat &_srcMat,Mat &_resultMat,Mat &_highlightMask,int _channel,int *_position,int _pixelNumber,Rect &_face):srcMat(_srcMat),highlightMask(_highlightMask),channel(_channel),resultMat(_resultMat),face(_face)
{
	position=_position;
	pixelNumber=_pixelNumber;
}
bool ImageInpaintingMethod::patchBelongsToKnownArea(Mat &fillRegion,int x,int y)
{
	for(int i=-(patchWindowSize>>1);i<=(patchWindowSize>>1);++i)
		for(int j=-(patchWindowSize>>1);j<=(patchWindowSize>>1);++j)
		{
			if(fillRegion.at<uchar>(y+j,x+i)==HIGHLIGHT_PIXEL_VALUE)
				return false;
		}
	return true;
}
double ImageInpaintingMethod::patchMeanSquaredDistance(Mat &srcMat,Mat &highlightMask,int x1,int y1,int x2,int y2,unsigned char pixelValue)
{
	double patchDis=0,rDis,gDis,bDis;
	int count=0;
	for(int i=-(patchWindowSize>>1);i<=(patchWindowSize>>1);++i)
		for(int j=-(patchWindowSize>>1);j<=(patchWindowSize>>1);++j)
		{
			if(highlightMask.at<uchar>(y1+j,x1+i)==pixelValue)
			{
				rDis=(double)srcMat.at<Vec3b>(y1+j,x1+i)[2]-(double)srcMat.at<Vec3b>(y2+j,x2+i)[2];
				gDis=(double)srcMat.at<Vec3b>(y1+j,x1+i)[1]-(double)srcMat.at<Vec3b>(y2+j,x2+i)[1];
				bDis=(double)srcMat.at<Vec3b>(y1+j,x1+i)[0]-(double)srcMat.at<Vec3b>(y2+j,x2+i)[0];
				count++;
				patchDis+=rDis*rDis+gDis*gDis+bDis*bDis;
			}
		}
	patchDis/=count;
	return patchDis;
}
double ImageInpaintingMethod::patchSparsity(Mat &srcMat,Mat &highlightMask,int x,int y,vector<double> &weight)
{
	double zp=0.0,result=0;
	double a,b;
	double Ns=0,Np=(2*((neighborhoodWindowSize>>1)-(patchWindowSize>>1))+1)*(2*((neighborhoodWindowSize>>1)-(patchWindowSize>>1))+1);
	for(int i=(patchWindowSize>>1)-(neighborhoodWindowSize>>1);i<=(neighborhoodWindowSize>>1)-(patchWindowSize>>1);++i)
		for(int j=(patchWindowSize>>1)-(neighborhoodWindowSize>>1);j<=(neighborhoodWindowSize>>1)-(patchWindowSize>>1);++j)
		{
			if(patchBelongsToKnownArea(highlightMask,x+i,y+j))
			{
				double dis=patchMeanSquaredDistance(srcMat,highlightMask,x,y,x+i,y+j,NOTHIGHLIGHT_PIXEL_VALUE);
				double w=exp(-dis/(sigma*sigma));
				weight.push_back(w);
				zp+=w;
				Ns++;
			}
		}
	for(vector<double>::iterator it=weight.begin();it!=weight.end();++it)
		*it/=zp;
	for(vector<double>::iterator it=weight.begin();it!=weight.end();++it)
		result+=(*it)*(*it);
	result*=Ns/Np;
	result=sqrt(result);
	a=(1-kesi)/(sqrt(Ns/Np)-sqrt(1.0/Np));
	b=kesi-a*sqrt(1.0/Np);
	return a*result+b;
}
void ImageInpaintingMethod::initPatchSparsity(Mat &srcMat,Mat &fillRegion,Rect &face,list<PatchSparsity *> &patchList,multimap<int,list<PatchSparsity *>::iterator> &key)
{
	int x=face.x,y=face.y,w=face.width,h=face.height;
	for(int i=x;i<w+x;++i)
		for(int j=y;j<y+h;++j)
		{
			insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,i,j);
		}
}
void ImageInpaintingMethod::updateSparsityList(Mat &srcMat,Mat &fillRegion,list< PatchSparsity *> &patchList,multimap<int,list< PatchSparsity *>::iterator> &key,int x,int y)
{
	int halfWindowSize=patchWindowSize>>1;
	for(int i=-halfWindowSize;i<=halfWindowSize;++i)
		for(int j=-halfWindowSize;j<=halfWindowSize;++j)
		{
			multimap<int,list<PatchSparsity *>::iterator>::iterator beg=key.lower_bound(x+y+i+j);
			if(beg!=key.end())
			{
				multimap<int,list<PatchSparsity *>::iterator>::iterator end=key.upper_bound(x+y+i+j);
				for(;beg!=end;++beg)
				{
					if((*(beg->second))->x==(x+i)&&(*(beg->second))->y==(y+j))
						break;
				}
				if(beg!=end)
				{
					delete *(beg->second);
					patchList.erase(beg->second);
					key.erase(beg);
				}
			}
		}
		//check four boundaries
		//up
		for(int i=-halfWindowSize,j=-halfWindowSize;i<=halfWindowSize;++i)
		{
			insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,x+i,y+j-1);
		}
		//down
		for(int i=-halfWindowSize,j=halfWindowSize;i<=halfWindowSize;++i)
		{
			insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,x+i,y+j+1);
		}
		//left
		for(int i=-halfWindowSize,j=-halfWindowSize;j<=halfWindowSize;++j)
		{
			insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,x+i-1,y+j);
		}
		//right
		for(int i=halfWindowSize,j=-halfWindowSize;j<=halfWindowSize;++j)
		{
			insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,x+i+1,y+j);
		}
		//check four corners
		insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,x-halfWindowSize-1,y-halfWindowSize-1);
		insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,x+halfWindowSize+1,y-halfWindowSize-1);
		insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,x-halfWindowSize-1,y+halfWindowSize+1);
		insertPatchSparsityIntoList(srcMat,fillRegion,patchList,key,x+halfWindowSize+1,y+halfWindowSize+1);
}
void ImageInpaintingMethod::insertPatchSparsityIntoList(Mat &srcMat,Mat &fillRegion,list< PatchSparsity *> &patchList,multimap<int,list< PatchSparsity *>::iterator> &key,int x,int y)
{
	if(BasisOperation::pixelIsBoundary(fillRegion,x,y))
	{
		multimap<int,list<PatchSparsity *>::iterator>::iterator beg,end;
		beg=key.lower_bound(x+y);
		if(beg!=key.end())
		{
			end=key.upper_bound(x+y);
			for(;beg!=end;++beg)
			{
				if((*(beg->second))->x==x&&(*(beg->second))->y==y)
					return;
			}
		}
		PatchSparsity *temp=new PatchSparsity();
		temp->x=x;
		temp->y=y;
		temp->sparsity=patchSparsity(srcMat,fillRegion,x,y,temp->weight);
		patchList.push_front(temp);
		key.insert(pair<int,list<PatchSparsity*>::iterator>(x+y,patchList.begin()));
	}
}
void ImageInpaintingMethod::removal(Mat &srcMat,Mat &resultMat,Mat &highlightMask,Rect &face)
{
	int x=face.x,y=face.y,w=face.width,h=face.height;
	Mat confidence=Mat::zeros(srcMat.rows,srcMat.cols,CV_32FC1);
	Mat fileRegion(srcMat.rows,srcMat.cols,CV_8UC1);
	highlightMask.copyTo(fileRegion);
	int inpaintPixelNumber=0;
	multimap<int,list<PatchSparsity *>::iterator> key;
	list<PatchSparsity *> patchSparsityList;
	PatchSparsity *tempPatchSparsity=NULL;
	initPatchSparsity(srcMat,fileRegion,face,patchSparsityList,key);
	int sz=patchSparsityList.size();
	for(int i=x;i<w+x;++i)
		for(int j=y;j<h+y;++j)
		{
			if(fileRegion.at<uchar>(j,i)==HIGHLIGHT_PIXEL_VALUE)
				inpaintPixelNumber++;
			else
				confidence.at<float>(j,i)=1.0f;
		}
		while(inpaintPixelNumber>0)
		{
			double maxPriority=-10,pixelConfidence;
			int inpaintX,inpaintY;
			vector<double> weight;
			for(list<PatchSparsity *>::iterator it=patchSparsityList.begin();it!=patchSparsityList.end();++it)
			{
				double priority,conf;
				conf=patchConfidence(fileRegion,confidence,(*it)->x,(*it)->y,NOTHIGHLIGHT_PIXEL_VALUE);
				priority=conf*(*it)->sparsity;
				if(priority>maxPriority)
				{
					pixelConfidence=conf;
					maxPriority=priority;
					inpaintX=(*it)->x;
					inpaintY=(*it)->y;
				}
			}
#ifdef PATCHCOMBINATION
			MinNHeap<PatchError> heap(candidatePathNumber);
			for(int i=x;i<w+x;++i)
				for(int j=y;j<y+h;++j)
				{
					if(patchBelongsToKnownArea(fileRegion,i,j))
					{
						double er=patchSSDError(resultMat,fileRegion,inpaintX,inpaintY,i,j,NOTHIGHLIGHT_PIXEL_VALUE);
						PatchError e(i,j,er);
						heap.insert(e);
					}
				}
#else
			int bestMatchX,BestMatchY;
			siglePathBestMatch(inpaintX,inpaintY,fileRegion,bestMatchX,BestMatchY,face,srcMat);
#endif

#ifdef PATCHCOMBINATION
			double normalizeSum=0;
			for(int i=0;i<heap.getSize();++i)
				normalizeSum+=heap.data[i].unnormalizedWeight;
#else
#endif
			for(int i=-(patchWindowSize>>1);i<=(patchWindowSize>>1);++i)
				for(int j=-(patchWindowSize>>1);j<=(patchWindowSize>>1);++j)
				{
					if(fileRegion.at<uchar>(inpaintY+j,inpaintX+i)==HIGHLIGHT_PIXEL_VALUE)
					{	
						double R=0,G=0,B=0;
#ifdef PATCHCOMBINATION
						for(int k=0;k<heap.getSize();++k)
						{
							R+=(double)resultMat.at<Vec3b>(heap.data[k].y+j,heap.data[k].x+i)[2]*heap.data[k].unnormalizedWeight/normalizeSum;
							G+=(double)resultMat.at<Vec3b>(heap.data[k].y+j,heap.data[k].x+i)[1]*heap.data[k].unnormalizedWeight/normalizeSum;
							B+=(double)resultMat.at<Vec3b>(heap.data[k].y+j,heap.data[k].x+i)[0]*heap.data[k].unnormalizedWeight/normalizeSum;
						}
						R=R>255?255:R;
						R=R<0?0:R;
						G=G>255?255:G;
						G=G<0?0:G;
						B=B>255?255:B;
						B=B<0?0:B;
#else
						R=resultMat.at<Vec3b>(BestMatchY+j,bestMatchX+i)[2];
						G=resultMat.at<Vec3b>(BestMatchY+j,bestMatchX+i)[1];
						B=resultMat.at<Vec3b>(BestMatchY+j,bestMatchX+i)[0];
#endif
						resultMat.at<Vec3b>(inpaintY+j,inpaintX+i)[2]=(uchar)R;
						resultMat.at<Vec3b>(inpaintY+j,inpaintX+i)[1]=(uchar)G;
						resultMat.at<Vec3b>(inpaintY+j,inpaintX+i)[0]=(uchar)B;
						inpaintPixelNumber--;
						confidence.at<float>(inpaintY+j,inpaintX+i)=pixelConfidence;
						fileRegion.at<uchar>(inpaintY+j,inpaintX+i)=NOTHIGHLIGHT_PIXEL_VALUE;
					}
				}
				updateSparsityList(srcMat,fileRegion,patchSparsityList,key,inpaintX,inpaintY);
		}
}
void ImageInpaintingMethod::siglePathBestMatch(int inpaintX,int inpaintY,Mat &fillRegion,int &bestMatchX,int &bestMatchY,Rect &face,Mat &srcMat)
{
	int x=face.x,y=face.y,w=face.width,h=face.height;
	double minError=initPathError;
	bestMatchX=x;
	bestMatchY=y;
	int halfWindowSize=(patchWindowSize>>1);
	for(int i=x+halfWindowSize;i<w+x-halfWindowSize;++i)
		for(int j=y+halfWindowSize;j<h+y-halfWindowSize;++j)
		{
			if(patchBelongsToKnownArea(fillRegion,i,j))
			{
				double error=patchSSDError(srcMat,fillRegion,inpaintX,inpaintY,i,j,NOTHIGHLIGHT_PIXEL_VALUE);
				if(error<minError)
				{
					minError=error;
					bestMatchX=i;
					bestMatchY=y;
				}
			}
		}
}
double ImageInpaintingMethod::patchConfidence(Mat &fillRegion,Mat &confidence,int x,int y,unsigned char pixelValue)
{
	double result=0;
	for(int i=-(patchWindowSize>>1);i<=(patchWindowSize>>1);++i)
		for(int j=-(patchWindowSize>>1);j<=(patchWindowSize>>1);++j)
		{
			if(fillRegion.at<uchar>(y+j,x+i)==pixelValue)
			{
				result+=confidence.at<float>(y+j,x+i);
			}
		}
	return result/(patchWindowSize*patchWindowSize);
}
double ImageInpaintingMethod::patchSSDError(Mat &srcMat,Mat &fillRegion,int x1,int y1,int x2,int y2,unsigned char pixelValue)
{
	double result=0,rDis,gDis,bDis;
	for(int i=-(patchWindowSize>>1);i<=(patchWindowSize>>1);++i)
		for(int j=-(patchWindowSize>>1);j<=(patchWindowSize>>1);++j)
		{
			if(fillRegion.at<uchar>(y1+j,x1+i)==pixelValue)
			{
				rDis=(double)srcMat.at<Vec3b>(y1+j,x1+i)[2]-(double)srcMat.at<Vec3b>(y2+j,x2+i)[2];
				gDis=(double)srcMat.at<Vec3b>(y1+j,x1+i)[1]-(double)srcMat.at<Vec3b>(y2+j,x2+i)[1];
				bDis=(double)srcMat.at<Vec3b>(y1+j,x1+i)[0]-(double)srcMat.at<Vec3b>(y2+j,x2+i)[0];
				result+=rDis*rDis+gDis*gDis+bDis*bDis;
			}
		}
	return result;
}
void PossionMethodThread::run()
{
	int w=face.width,h=face.height,x=face.x,y=face.y;
	SpMat A(pixelNumber,pixelNumber);
	Eigen::VectorXd b(pixelNumber),X(pixelNumber);
	vector<T> tripleList;
	A.setZero();
	b.setZero();
	X.setZero();
	int count=0;
	double gradientNormal;
	for(int i=x;i<w+x;++i)
		for(int j=y;j<h+y;++j)
		{
			if(highlightMask.at<uchar>(j,i)==HIGHLIGHT_PIXEL_VALUE)
			{
				tripleList.push_back(T(count,count,4));
#ifdef POSSION_HSV
				gradientNormal=sqrt(((double)srcMat.at<Vec3f>(j,i)[channel]-(double)srcMat.at<Vec3f>(j-1,i)[channel])*((double)srcMat.at<Vec3f>(j,i)[channel]-(double)srcMat.at<Vec3f>(j-1,i)[channel])+((double)srcMat.at<Vec3f>(j,i)[channel]-(double)srcMat.at<Vec3f>(j,i-1)[channel])*((double)srcMat.at<Vec3f>(j,i)[channel]-(double)srcMat.at<Vec3f>(j,i-1)[channel]));
#else
				gradientNormal=sqrt(((double)srcMat.at<Vec3b>(j,i)[channel]-(double)srcMat.at<Vec3b>(j-1,i)[channel])*((double)srcMat.at<Vec3b>(j,i)[channel]-(double)srcMat.at<Vec3b>(j-1,i)[channel])+((double)srcMat.at<Vec3b>(j,i)[channel]-(double)srcMat.at<Vec3b>(j,i-1)[channel])*((double)srcMat.at<Vec3b>(j,i)[channel]-(double)srcMat.at<Vec3b>(j,i-1)[channel]));
#endif
				if(j!=y&&highlightMask.at<uchar>(j-1,i)==HIGHLIGHT_PIXEL_VALUE)
				{
					if(fabs(gradientNormal)>0.001)
					{
#ifdef POSSION_HSV
						b(count)+=possionAttenuationRatio*pow(gradientNormal,-0.05)*((double)srcMat.at<Vec3f>(j,i)[channel]-(double)srcMat.at<Vec3f>(j-1,i)[channel]);
#else
						b(count)+=possionAttenuationRatio*pow(gradientNormal,-0.05)*((double)srcMat.at<Vec3b>(j,i)[channel]*4-(double)srcMat.at<Vec3b>(j-1,i)[channel]-(double)srcMat.at<Vec3b>(j+1,i)[channel]-(double)srcMat.at<Vec3b>(j,i-1)[channel]-(double)srcMat.at<Vec3b>(j,i+1)[channel]);
#endif
					}
					tripleList.push_back(T(count,position[(j-1)*srcMat.cols+i]-1,-1));
				}
				else
#ifdef POSSION_HSV
					b(count)+=(double)srcMat.at<Vec3f>(j-1,i)[channel];
#else
					b(count)+=(double)srcMat.at<Vec3b>(j-1,i)[channel];
#endif
				if(j!=(h+y-1)&&highlightMask.at<uchar>(j+1,i)==HIGHLIGHT_PIXEL_VALUE)
				{
					if(fabs(gradientNormal)>0.001)
					{
#ifdef POSSION_HSV
						b(count)+=possionAttenuationRatio*pow(gradientNormal,-0.05)*((double)srcMat.at<Vec3f>(j,i)[channel]-(double)srcMat.at<Vec3f>(j+1,i)[channel]);
#else
						b(count)+=possionAttenuationRatio*pow(gradientNormal,-0.05)*((double)srcMat.at<Vec3b>(j,i)[channel]*4-(double)srcMat.at<Vec3b>(j-1,i)[channel]-(double)srcMat.at<Vec3b>(j+1,i)[channel]-(double)srcMat.at<Vec3b>(j,i-1)[channel]-(double)srcMat.at<Vec3b>(j,i+1)[channel]);
#endif
					}
					tripleList.push_back(T(count,position[(j+1)*srcMat.cols+i]-1,-1));
				}
				else
#ifdef POSSION_HSV
					b(count)+=(double)srcMat.at<Vec3f>(j+1,i)[channel];
#else
					b(count)+=(double)srcMat.at<Vec3b>(j+1,i)[channel];
#endif
				if(i!=x&&highlightMask.at<uchar>(j,i-1)==HIGHLIGHT_PIXEL_VALUE)
				{
					if(fabs(gradientNormal)>0.001)
					{
#ifdef POSSION_HSV
						b(count)+=possionAttenuationRatio*pow(gradientNormal,-0.05)*((double)srcMat.at<Vec3f>(j,i)[channel]-(double)srcMat.at<Vec3f>(j,i-1)[channel]);
#else
						b(count)+=possionAttenuationRatio*pow(gradientNormal,-0.05)*((double)srcMat.at<Vec3b>(j,i)[channel]*4-(double)srcMat.at<Vec3b>(j-1,i)[channel]-(double)srcMat.at<Vec3b>(j+1,i)[channel]-(double)srcMat.at<Vec3b>(j,i-1)[channel]-(double)srcMat.at<Vec3b>(j,i+1)[channel]);
#endif
					}
					tripleList.push_back(T(count,position[j*srcMat.cols+i-1]-1,-1));
				}
				else
#ifdef POSSION_HSV
					b(count)+=(double)srcMat.at<Vec3f>(j,i-1)[channel];
#else
					b(count)+=(double)srcMat.at<Vec3b>(j,i-1)[channel];
#endif
				if(i!=(w+x-1)&&highlightMask.at<uchar>(j,i+1)==HIGHLIGHT_PIXEL_VALUE)
				{
					tripleList.push_back(T(count,position[j*srcMat.cols+i+1]-1,-1));
					if(fabs(gradientNormal)>0.001)
					{
#ifdef POSSION_HSV
						b(count)+=possionAttenuationRatio*pow(gradientNormal,-0.05)*((double)srcMat.at<Vec3f>(j,i)[channel]-(double)srcMat.at<Vec3f>(j,i+1)[channel]);
#else
						b(count)+=possionAttenuationRatio*pow(gradientNormal,-0.05)*((double)srcMat.at<Vec3b>(j,i)[channel]*4-(double)srcMat.at<Vec3b>(j-1,i)[channel]-(double)srcMat.at<Vec3b>(j+1,i)[channel]-(double)srcMat.at<Vec3b>(j,i-1)[channel]-(double)srcMat.at<Vec3b>(j,i+1)[channel]);
#endif
					}
				}
				else
#ifdef POSSION_HSV
					b(count)+=(double)srcMat.at<Vec3f>(j,i+1)[channel];
#else
					b(count)+=(double)srcMat.at<Vec3b>(j,i+1)[channel];
#endif
				count++;
			}
		}
		A.setFromTriplets(tripleList.begin(),tripleList.end());
		Eigen::SimplicialCholesky< Eigen::SparseMatrix<double> > slu;
		slu.compute(A.transpose()*A);
		X=slu.solve(A.transpose()*b);
		double pixelValue;
		for(int i=x;i<w+x;++i)
			for(int j=y;j<h+y;++j)
			{
				if(highlightMask.at<uchar>(j,i)==HIGHLIGHT_PIXEL_VALUE)
				{
					pixelValue=X(position[j*srcMat.cols+i]-1);
#ifdef POSSION_HSV
					pixelValue=pixelValue>100?100:pixelValue;
					pixelValue=pixelValue<0?0:pixelValue;
					resultMat.at<Vec3f>(j,i)[channel]=pixelValue;
#else
					pixelValue=pixelValue>255?255:pixelValue;
					pixelValue=pixelValue<0?0:pixelValue;
					resultMat.at<Vec3b>(j,i)[channel]=(uchar)pixelValue;
#endif
				}
			}
}
void HighLightRemoval::removal(Mat &srcMat,Mat &resultMat,Mat &highlightMask,Rect &face,unsigned char mode)
{
	if(mode & HIGHLIGHT_REMOVAL_POSSION_MATHOD)
	{
		int x=face.x,y=face.y,w=face.width,h=face.height;
		int *position=new int[srcMat.rows*srcMat.cols];
		memset(position,0,srcMat.rows*srcMat.cols*sizeof(int));
		int pixleNumber=0;
		for(int i=x;i<x+w;++i)
			for(int j=y;j<y+h;++j)
			{
				if(highlightMask.at<uchar>(j,i)==HIGHLIGHT_PIXEL_VALUE)
				{
					pixleNumber++;
					position[j*srcMat.cols+i]=pixleNumber;
				}
			}
#ifdef POSSION_HSV
		Mat labMat(srcMat.rows,srcMat.cols,CV_32FC3);
		ColorSpaceTransition::rgb2Lab(srcMat,labMat);
		PossionMethodThread lChannel(labMat,labMat,highlightMask,2,position,pixleNumber,face);
		lChannel.start();
		lChannel.wait();
		ColorSpaceTransition::lab2Rgb(labMat,resultMat);
#else
#ifdef USINGTHREAD
		PossionMethodThread rChannel(srcMat,resultMat,highlightMask,2,position,pixleNumber,face);
		PossionMethodThread gChannel(srcMat,resultMat,highlightMask,1,position,pixleNumber,face);
		PossionMethodThread bChannel(srcMat,resultMat,highlightMask,0,position,pixleNumber,face);
		rChannel.start();
		gChannel.start();
		bChannel.start();
		rChannel.wait();
		gChannel.wait();
		bChannel.wait();
#else
#endif
#endif
		delete [] position;
	}
	if(mode&HIGHLIGHT_REMOVAL_INPAINTING_MATHOD)
	{
		ImageInpaintingMethod::removal(srcMat,resultMat,highlightMask,face);
	}
	if(mode&HIGHLIGHT_REMOVAL_MAPPING_MATHOD)
	{
		blur(highlightMask,highlightMask,Size(20,20));
		BasisOperation::localEnhencementUsingMappingMethod(resultMat,&highlightMask,0.5,0.45);
	}
	if(mode&HIGHLIGHT_REMOVAL_COLOR_LEVEL_METHOD)
	{
		Mat temp=Mat::zeros(highlightMask.rows,highlightMask.cols,CV_8UC1);
		blur(highlightMask,temp,Size(25,25));
		for(int i=0;i<highlightMask.cols;++i)
			for(int j=0;j<highlightMask.rows;++j)
			{
				if(highlightMask.at<uchar>(j,i)==HIGHLIGHT_PIXEL_VALUE)
					highlightMask.at<uchar>(j,i)=temp.at<uchar>(j,i);
			}
		BasisOperation::colorLevel(srcMat,resultMat,0,255,140);
		int w=srcMat.cols,h=srcMat.rows;
		double weight,redChannelValue,greenChannelValue,blueChannelValue;
		for(int i=0;i<w;++i)
			for(int j=0;j<h;++j)
			{
				weight=highlightMask.at<uchar>(j,i)/255.0;
				redChannelValue=weight*resultMat.at<Vec3b>(j,i)[2]+(1-weight)*srcMat.at<Vec3b>(j,i)[2];
				greenChannelValue=weight*resultMat.at<Vec3b>(j,i)[1]+(1-weight)*srcMat.at<Vec3b>(j,i)[1];
				blueChannelValue=weight*resultMat.at<Vec3b>(j,i)[0]+(1-weight)*srcMat.at<Vec3b>(j,i)[0];
				resultMat.at<Vec3b>(j,i)[2]=(unsigned char)redChannelValue;
				resultMat.at<Vec3b>(j,i)[1]=(unsigned char)greenChannelValue;
				resultMat.at<Vec3b>(j,i)[0]=(unsigned char)blueChannelValue;
			}
	}
}