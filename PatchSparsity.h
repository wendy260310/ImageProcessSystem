#ifndef PATCH_SPARSITY_H
#define PATCH_SPARSITY_H
#include "parameters.h"
class PatchSparsity
{
public:
	int x,y;
	double sparsity;
	vector<double> weight;
	bool operator==(const PatchSparsity &p)const
	{
		return x==p.x&&y==p.y;
	}
};
class PatchSparsityEqual
{
public:
	bool operator()(const PatchSparsity *a,const PatchSparsity *);
};
#endif