#ifndef HEADER_H
#define HEADER_H
#ifdef EXPORT_DLL
class QPoint
{
public:
	QPoint()
	{

	}
	QPoint(int x,int y):_x(x),_y(y)
	{

	}
	int inline x() const
	{
		return _x;
	}
	int inline y() const
	{
		return _y;
	}
private:
	int _x;
	int _y;
};
#else
#include <QLabel>
#include <QSlider>
#include <QImage>
#include <QListWidgetItem>
#include <QIcon>
#include <QMutex>
#include <QMessageBox>
#include <QThread>
#include <QSemaphore>
#include <QMouseEvent>
#include <QPainter>
#include <QtGui/QFileDialog>
#include <QtGui/QMainWindow>
#include <QRadioButton>
#include <QDir>
#include <QLabel>
#include <QDialog>
#include <QCheckBox>
#endif
#include <math.h>
#include <Eigen/Sparse>
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <vector>
#include <math.h>
#include <memory>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>
using namespace cv;
using namespace std;
template<typename U> class MatWrapper
{
public:
	typedef U STEP;
	MatWrapper()
	{

	}
	MatWrapper(int h,int w,int _type):mat(h,w,_type)
	{

	}
	Mat & get()
	{
		return mat;
	}
	MatWrapper<U> & operator=(MatWrapper<U> &m)
	{
		if(&m!=this)
		{
			mat=m.get();
		}
	}
	MatWrapper(MatWrapper<U> &w):mat(w.get())
	{

	}
	Mat * operator->()
	{
		return &mat;
	}
private:
	Mat mat;
};
//using namespace stdext;
typedef Eigen::SparseMatrix<double> SpMat;
typedef Eigen::Triplet<double> Tri;
#ifdef SINGLE
#define REAL float
#else /* not SINGLE */
#define REAL double
#endif /* not SINGLE */s
#define VOID void
#endif