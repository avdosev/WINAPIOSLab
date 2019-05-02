#-------------------------------------------------
#
# Project created by QtCreator 2018-10-24T14:46:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app
CONFIG += c++14
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        mainwindow.cpp \
    tyristmanual.cpp \
    main_client.cpp \
    mestootduxavalidator.cpp \
    databasecontroller.cpp \
    filestream.cpp \
    datastream.cpp \
    pipestream.cpp \
    thread.cpp

HEADERS += \
        mainwindow.h \
    tyristmanual.h \
    mestootduxavalidator.h \
    tyristmanualqlistwidgetitem.h \
    databaseprototype.h \
    databasecontroller.h \
    filestream.h \
    datastream.h \
    pipestream.h \
    server_command.h \
    config_pipe_naming.h \
    thread.h

FORMS += \
        mainwindow.ui

RESOURCES +=

DISTFILES +=
