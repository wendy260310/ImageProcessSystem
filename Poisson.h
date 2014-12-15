#ifndef POSSION_H
#define POSSION_H
#include "header.h"
enum Channle{FIRST=0,SECOND=1,THIRD=2};
class Poisson
{
public:
	template<typename S,typename U> void static poissonEditing(S &srcMat,S &resultMat,U &regionMask,vector<int> position,int regionPixelNumber,Channle channel,double lowBoundary,double highBoundary)
	{
		SpMat A(regionPixelNumber,regionPixelNumber);
		Eigen::VectorXd x(regionPixelNumber),b(regionPixelNumber);
		A.setZero();
		x.setZero();
		b.setZero();
		vector<Tri> tripleList;
		int count=0;
		int w=srcMat->cols,h=srcMat->rows;
		for(int i=0;i<h;++i)
			for(int j=0;j<w;++j)
			{
				if(regionMask->at<U::STEP>(i,j)==PIXEL_SELECTED_VALUE)
				{
					//please pay attention to the region boundary
					tripleList.push_back(Tri(count,count,4));
					//up
					if(i!=0&&regionMask->at<U::STEP>(i-1,j)==PIXEL_SELECTED_VALUE)
					{
						tripleList.push_back(Tri(count,position[(i-1)*w+j],-1));
						b(count)+=(double)srcMat->at<S::STEP>(i,j)[channel]-(double)srcMat->at<S::STEP>(i-1,j)[channel];
					}
					else
						b(count)+=srcMat->at<S::STEP>(i-1,j)[channel];
					//down
					if(i!=(h-1)&&regionMask->at<U::STEP>(i+1,j)==PIXEL_SELECTED_VALUE)
					{
						tripleList.push_back(Tri(count,position[(i+1)*w+j],-1));
						b(count)+=(double)srcMat->at<S::STEP>(i,j)[channel]-(double)srcMat->at<S::STEP>(i+1,j)[channel];
					}
					else
						b(count)+=srcMat->at<S::STEP>(i+1,j)[channel];
					//left
					if(j!=0&&regionMask->at<U::STEP>(i,j-1)==PIXEL_SELECTED_VALUE)
					{
						tripleList.push_back(Tri(count,position[i*w+j-1],-1));
						b(count)+=(double)srcMat->at<S::STEP>(i,j)[channel]-(double)srcMat->at<S::STEP>(i,j-1)[channel];
					}

					else
						b(count)+=srcMat->at<S::STEP>(i,j-1)[channel];
					//right
					if(j!=(w-1)&&regionMask->at<U::STEP>(i,j+1)==PIXEL_SELECTED_VALUE)
					{
						tripleList.push_back(Tri(count,position[i*w+j+1],-1));
						b(count)+=(double)srcMat->at<S::STEP>(i,j)[channel]-(double)srcMat->at<S::STEP>(i,j+1)[channel];
					}
					else
						b(count)+=srcMat->at<S::STEP>(i,j+1)[channel];
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
					if(regionMask->at<uchar>(i,j)==PIXEL_SELECTED_VALUE)
					{
						pixelValue=x(position[i*w+j]);
						pixelValue=pixelValue<lowBoundary?lowBoundary:pixelValue;
						pixelValue=pixelValue>highBoundary?highBoundary:pixelValue;
						resultMat->at<S::STEP>(i,j)[channel]=(uchar)pixelValue;
					}
				}
	}
};
#endif