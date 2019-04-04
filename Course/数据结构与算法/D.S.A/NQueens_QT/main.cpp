#include "NQueens_QT.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NQueens_QT w;
	w.show();
	return a.exec();
}
