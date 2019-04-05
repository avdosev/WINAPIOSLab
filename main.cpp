#include "mainwindow.h"
#include <QApplication>
#include <QTime>

#include <datastream.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
    qsrand( QTime::currentTime().msec() );
	return a.exec();
}
