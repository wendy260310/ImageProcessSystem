#ifndef IMAGE_TRIANGLE_H
#define IMAGE_TRIANGLE_H
#include <vector>
using namespace std;
class ImageTriangle
{
public:
	void static bulitTri(vector<double> &pointX,vector<double> &pointY,struct triangulateio &vorout);
	void static initTriangulateio(struct triangulateio &io);
	void static freeTriangulateio(struct triangulateio &io);
};
#endif