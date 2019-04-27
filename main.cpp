#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>

#include "database.h"


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static FILE* messageFile = fopen("logs.txt", "w");
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(messageFile, "Debug:\t%s\t(file: %s line: %u time: %s)\n", localMsg.constData(), context.file, context.line, QTime::currentTime().toString("hh:mm:ss.zzz").toStdString().c_str());
        break;
    case QtInfoMsg:
        fprintf(messageFile, "Info:\t%s\t(file: %s line: %u time: %s)\n", localMsg.constData(), context.file, context.line, QTime::currentTime().toString("hh:mm:ss.zzz").toStdString().c_str());
        break;
    case QtWarningMsg:
        fprintf(messageFile, "Warning:\t%s\t(file: %s line: %u time: %s)\n", localMsg.constData(), context.file, context.line, QTime::currentTime().toString("hh:mm:ss.zzz").toStdString().c_str());
        break;
    case QtCriticalMsg:
        fprintf(messageFile, "Critical:\t%s\t(file: %s line: %u time: %s)\n", localMsg.constData(), context.file, context.line, QTime::currentTime().toString("hh:mm:ss.zzz").toStdString().c_str());
        break;
    case QtFatalMsg:
        fprintf(messageFile, "Fatal:\t%s\t(file: %s line: %u time: %s)\n", localMsg.constData(), context.file, context.line, QTime::currentTime().toString("hh:mm:ss.zzz").toStdString().c_str());
        abort();
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    qInstallMessageHandler(myMessageOutput); // устанавливаем обработку qdebug в логфайл

    MainWindow w;
    w.show();

    qsrand( QTime::currentTime().msec() );

	return a.exec();
}
