#include "Memory.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Memory w;
	w.show();
	return a.exec();
}
