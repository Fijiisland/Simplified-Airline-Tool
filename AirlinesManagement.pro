#-------------------------------------------------
#
# Project created by QtCreator 2019-03-11T08:29:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AirlinesManagement
TEMPLATE = app

RC_ICONS = logo.ico


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    airplane.h \
    _utility.h \
    _blendSort.h \
    _InsertionSort.h

FORMS    += mainwindow.ui

RESOURCES += \
    source.qrc

