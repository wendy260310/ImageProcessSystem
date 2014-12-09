#include "ColorSpaceTransitionClass.h"
void ColorSpaceTransition::rgb2Lab(Mat &rgbMat,Mat &labMat)
{
	int w=rgbMat.cols,h=rgbMat.rows;
	double thd=0.008856,R,G,B,X,Y,Z,fX,fY,fZ,Y3,l,a,b;
	bool XT,YT,ZT;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			R=rgbMat.at<Vec3b>(j,i)[2]/255.0;
			G=rgbMat.at<Vec3b>(j,i)[1]/255.0;
			B=rgbMat.at<Vec3b>(j,i)[0]/255.0;
			X=(0.412453*R+0.357580*G+0.180423*B)/0.950456;
			Y=0.212671*R+0.715160*G+0.072169*B;
			Z=(0.019334*R+0.119193*G+0.950227*B)/1.088754;
			XT=(X>thd);
			YT=(Y>thd);
			ZT=(Z>thd);
			Y3=pow(Y,1.0/3.0);
			fX=XT?pow(X,1.0/3.0):(7.787*X+16.0/116.0);
			fY=YT?Y3:(7.787*Y+16.0/116.0);
			fZ=ZT?pow(Z,1.0/3.0):(7.787*Z+16.0/116.0);
			l=YT?((float)(116*Y3-16.0)):(903.3*Y);
			l=l>100?100:l;
			l=l<0?0:l;
			a=500*(fX-fY);
			a=a>127?127:a;
			a=a<-128?-128:a;
			b=200*(fY-fZ);
			b=b>127?127:b;
			b=b<-128?-128:b;
			labMat.at<Vec3f>(j,i)[2]=l;
			labMat.at<Vec3f>(j,i)[1]=a;
			labMat.at<Vec3f>(j,i)[0]=b;
		}
}
void ColorSpaceTransition::lab2Rgb(Mat &labMat,Mat &rgbMat)
{
	double t1=0.008856,t2=0.206893,L,a,b,fY,fX,X,fZ,Z,R,G,B,Y;
	bool YT,XT,ZT;
	int w=labMat.cols,h=labMat.rows;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			L=labMat.at<Vec3f>(j,i)[2];
			a=labMat.at<Vec3f>(j,i)[1];
			b=labMat.at<Vec3f>(j,i)[0];
			fY=pow((L+16.0)/116.0,3);
			YT=(fY>t1);
			fY=YT?fY:L/903.3;
			Y=fY;
			fY=YT?pow(fY,1.0/3.0):(7.787*fY+16.0/116.0);
			fX=a/500.0+fY;
			XT=fX>t2;
			X=XT?pow(fX,3):((fX-16.0/116.0)/7.787);
			fZ=fY-b/200.0;
			ZT=fZ>t2;
			Z=ZT?pow(fZ,3):((fZ-16.0/116.0)/7.787);

			X=X*0.950456;
			Z=Z*1.088754;
			R=3.240479*X-1.537150*Y-0.498535*Z;
			G=-0.969256*X+1.875992*Y+0.041556*Z;
			B=0.055648*X-0.204043*Y+1.057311*Z;
			R=(R>1)?1:R;
			R=(R<0)?0:R;
			G=(G>1)?1:G;
			G=(G<0)?0:G;
			B=(B>1)?1:B;
			B=(B<0)?0:B;
			rgbMat.at<Vec3b>(j,i)[2]=(uchar)(R*255);
			rgbMat.at<Vec3b>(j,i)[1]=(uchar)(G*255);
			rgbMat.at<Vec3b>(j,i)[0]=(uchar)(B*255);
		}
}
void ColorSpaceTransition::hsv2Rgb(Mat &hsvMat,Mat &rgbMat)
{
	int hi;
	double f,p,q,t,r,g,b;
	int w=hsvMat.cols,h=hsvMat.rows;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			hi=(int)(hsvMat.at<Vec3f>(j,i)[2]/60.0)%6;
			f=hsvMat.at<Vec3f>(j,i)[2]/60.0-hi;
			p=hsvMat.at<Vec3f>(j,i)[0]*(1-hsvMat.at<Vec3f>(j,i)[1]);
			q=hsvMat.at<Vec3f>(j,i)[0]*(1-f*hsvMat.at<Vec3f>(j,i)[1]);
			t=hsvMat.at<Vec3f>(j,i)[0]*(1-(1-f)*hsvMat.at<Vec3f>(j,i)[1]);
			switch(hi)
			{
			case 0:
				r=hsvMat.at<Vec3f>(j,i)[0]*255;
				g=t*255;
				b=p*255;
				break;
			case 1:
				r=q*255;
				g=hsvMat.at<Vec3f>(j,i)[0]*255;
				b=p*255;
				break;
			case 2:
				r=p*255;
				g=hsvMat.at<Vec3f>(j,i)[0]*255;
				b=t*255;
				break;
			case 3:
				r=p*255;
				g=q*255;
				b=hsvMat.at<Vec3f>(j,i)[0]*255;
				break;
			case 4:
				r=t*255;
				g=p*255;
				b=hsvMat.at<Vec3f>(j,i)[0]*255;
				break;
			case 5:
				r=hsvMat.at<Vec3f>(j,i)[0]*255;
				g=(p*255);
				b=(q*255);
				break;
			}
			r=r>255?255:r;
			r=r<0?0:r;
			g=g>255?255:g;
			g=g<0?0:g;
			b=b>255?255:b;
			b=b<0?0:b;
			rgbMat.at<Vec3b>(j,i)[2]=(uchar)r;
			rgbMat.at<Vec3b>(j,i)[1]=(uchar)g;
			rgbMat.at<Vec3b>(j,i)[0]=(uchar)b;
		}
}
void ColorSpaceTransition::rgb2Hsv(Mat &rgbMat,Mat &hsvMat)
{
	double r,g,b,max,min;
	float pixelValue;
	int w=rgbMat.cols,h=rgbMat.rows;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			r=rgbMat.at<Vec3b>(j,i)[2]/255.0;
			g=rgbMat.at<Vec3b>(j,i)[1]/255.0;
			b=rgbMat.at<Vec3b>(j,i)[0]/255.0;
			max=r>(g>b?g:b)?r:(g>b?g:b);
			min=r<(g<b?g:b)?r:(g<b?g:b);
			do 
			{
				if(!(max>min)&&!(min>max))
				{
					pixelValue=0;
					break;
				}
				if((!(max>r)&&!(r>max))&&g>=b)
				{
					pixelValue=60*(g-b)/(max-min);
					break;
				}
				if((!(max>r)&&!(r>max))&&g<b)
				{
					pixelValue=60*(g-b)/(max-min)+360;
					break;
				}
				if(!(max>g)&&!(g>max))
				{
					pixelValue=60*(b-r)/(max-min)+120;
					break;
				}
				if(!(max>b)&&!(b>max))
				{
					pixelValue=60*(r-g)/(max-min)+240;
					break;
				}
			} while (0);
			pixelValue=pixelValue>360?360:pixelValue;
			pixelValue=pixelValue<0?0:pixelValue;
			hsvMat.at<Vec3f>(j,i)[2]=pixelValue;
			if(!(max>0)&&!(0>max))
				hsvMat.at<Vec3f>(j,i)[1]=0;
			else
			{
				pixelValue=1-min/max;
				pixelValue=pixelValue>1?1:pixelValue;
				pixelValue=pixelValue<0?0:pixelValue;
				hsvMat.at<Vec3f>(j,i)[1]=pixelValue;
			}
			hsvMat.at<Vec3f>(j,i)[0]=max;
		}

}
void ColorSpaceTransition::rgb2Tsl(Mat &rgbMat,Mat &tslMat)
{
	int w=rgbMat.cols,h=rgbMat.rows;
	double R,G,B,_r,_g,T,S,L;
	for(int i=0;i<w;++i)
		for(int j=0;j<h;++j)
		{
			R=rgbMat.at<Vec3b>(j,i)[2]/255.0;
			G=rgbMat.at<Vec3b>(j,i)[1]/255.0;
			B=rgbMat.at<Vec3b>(j,i)[0]/255.0;
			L=0.299*R+0.587*G+0.114*B;
			_r=(R/(R+G+B)-1.0/3.0);
			_g=(G/(R+G+B)-1.0/3.0);
			S=pow(1.8*(_r*_r+_g*_g),0.5);
			if(_g>0)
			{
				T=atan(_r/_g)/(2*pai)+0.25;
			}
			else
				if(_g<0)
				{
					T=atan(_r/_g)/(2*pai)+0.75;
				}
				else
					T=0;
			T=T>1?1:T;
			T=T<0?0:T;
			S=S>1?1:S;
			S=S<0?0:S;
			L=L>1?1:L;
			L=L<0?0:L;
			tslMat.at<Vec3f>(j,i)[2]=T;
			tslMat.at<Vec3f>(j,i)[1]=S;
			tslMat.at<Vec3f>(j,i)[0]=L;
		}
}