#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>

#include "database.h"

#include "thread.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static FILE* messageFile = fopen("logs.txt", "w");
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(messageFile, "Debug:\t%s\t(file: %s line: %u)\n", localMsg.constData(), context.file, context.line);
        break;
    case QtInfoMsg:
        fprintf(messageFile, "Info:\t%s\t(%s:%u)\n", localMsg.constData(), context.file, context.line);
        break;
    case QtWarningMsg:
        fprintf(messageFile, "Warning:\t%s\t(%s:%u)\n", localMsg.constData(), context.file, context.line);
        break;
    case QtCriticalMsg:
        fprintf(messageFile, "Critical:\t%s\t(%s:%u)\n", localMsg.constData(), context.file, context.line);
        break;
    case QtFatalMsg:
        fprintf(messageFile, "Fatal:\t%s\t(%s:%u)\n", localMsg.constData(), context.file, context.line);
        abort();
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    qInstallMessageHandler(myMessageOutput); // устанавливаем обработку qdebug в логфайл

    auto controller = DataBaseController(new DataBase()); // создаем вне класса ui

    MainWindow w(controller);
    w.show();

    qsrand( QTime::currentTime().msec() );
	return a.exec();
}
