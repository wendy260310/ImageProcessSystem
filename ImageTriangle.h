#ifndef IMAGE_TRIANGLE_H
#define IMAGE_TRIANGLE_H
#ifdef SINGLE
#define REAL float
#else /* not SINGLE */
#define REAL double
#endif /* not SINGLE */s
#define VOID void
#include <vector>
using namespace std;
class ImageTriangle
{
public:
	void static bulitTri(vector<double> &pointX,vector<double> &pointY,struct triangulateio &vorout);
};
#endif