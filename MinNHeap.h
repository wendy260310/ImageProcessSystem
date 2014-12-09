#ifndef MIN_N_HEAP_H
#define MIN_N_HEAP_H
#include "parameters.h"
class PatchError
{
public:
	PatchError(){x=0;y=0;error=initPathError;}
	PatchError(int _x,int _y,double _error){x=_x;y=_y;error=_error;unnormalizedWeight=exp(-error*weightFunctionH);}
	~PatchError(){}
	bool operator<(PatchError &p) const {return error<p.error;}
	int x;
	int y;
	double error;
	double unnormalizedWeight;
};
template<class T>
	class MinNHeap
	{
	public:
		MinNHeap(int n):N(n)
		{
			size=0;
			if(n==1)
				data=new T();
			else
				data=new T[n];
		}
		~MinNHeap()
		{
			if(N==1)
				delete data;
			else
				delete []data;
		}
		void insert(const T &e)
		{
			if(size<N)
			{
				memcpy(data+size,&e,sizeof(T));
				shiftUp(size);
				++size;
			}
			else
			{
				if(e<data[0])
				{
					memcpy(data,&e,sizeof(T));
					shiftDown(0);
				}
			}
		}
		int inline getSize()const{return size;}
		int inline getCapacity()const{return N;}
		T *data;
	private:
		void shiftUp(int index)
		{
			if(index>size)
				return;
			T temp;
			memcpy(&temp,data+index,sizeof(T));
			int x=(index-1)>>1,y=index;
			while(x>=0&&x!=y)
			{
				if(*(data+x)<temp)
				{
					memcpy(data+y,data+x,sizeof(T));
					y=x;
					x=(x-1)/2;
				}
				else
					break;
			}
			memcpy(data+y,&temp,sizeof(T));
		}
		void shiftDown(int index)
		{
			if(index>N/2)
				return;
			T temp;
			memcpy(&temp,data+index,sizeof(T));
			int x=index,y;
			while(x<=N-1)
			{
				y=2*x+1;
				if((y+1)<=(N-1)&&data[y]<data[y+1])
				{
					++y;
				}
				if(y<=N-1&&temp<data[y])
				{
					memcpy(data+x,data+y,sizeof(T));
					x=y;
				}
				else
					break;
			}
			memcpy(data+x,&temp,sizeof(T));
		}
		const int N;
		int size;
	};
#endif