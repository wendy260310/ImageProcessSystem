#include "imageprocesssystem.h"
#include <QtGui/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageProcessSystem w;
	w.show();
	return a.exec();
}
