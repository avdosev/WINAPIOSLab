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
    DataStream fin;
    QString dir = "C:\\Users\\avdosev\\Desktop\\puk.txt";
    if (fin.open(dir, DataStream::app) || fin.open(dir, DataStream::in | DataStream::trunc)) {
        fin << QString("соси писос");
        fin << 1231;
    } else {
        qDebug() << "лежать + сосатъ";
    }
	return a.exec();
}
