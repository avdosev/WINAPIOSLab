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
    view/mainwindow.cpp \
    tyristmanual.cpp \
    main_client.cpp \
    services/validator/mestootduxavalidator.cpp \
    databasecontroller.cpp \
    services/stream/filestream.cpp \
    services/stream/datastream.cpp \
    services/stream/pipestream.cpp \
    services/thread/thread.cpp

HEADERS += \
    view/mainwindow.h \
    tyristmanual.h \
    services/validator/mestootduxavalidator.h \
    tyristmanualqlistwidgetitem.h \
    databasecontroller.h \
    services/stream/filestream.h \
    services/stream/datastream.h \
    services/stream/pipestream.h \
    services/thread/thread.h \
    config/server_command.h \
    config/pipe_naming.h

FORMS += \
    ui/mainwindow.ui
