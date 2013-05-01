#-------------------------------------------------
#
# Project created by QtCreator 2013-05-01T17:24:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple-qt-thread-example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    worker.cpp

HEADERS  += mainwindow.h \
    worker.h

FORMS    += mainwindow.ui
