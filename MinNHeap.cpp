#include "MinNHeap.h"
template <class T> MinNHeap<T>::MinNHeap(int n):N(n)
{
	size=0;
	if(n==1)
		data=new T();
	else
		data=new T[n];
}
template <class T >void MinNHeap<T>::shiftUp(int index)
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
template <class T> void  MinNHeap<T>::shiftDown(int index)
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
template <class T> MinNHeap<T>::~MinNHeap()
{
	if(N==1)
		delete data;
	else
		delete []data;
}
template<class T> void MinNHeap<T>::insert(const T &e)
{
	if(size<N)
	{
		memcpy(data+size,&e,sizeof(T));
		shiftUp(size);
		++size;
	}
	else
	{
		if(e<*data)
		{
			memcpy(data,&e,sizeof(T));
			shiftDown(0);
		}
	}
}