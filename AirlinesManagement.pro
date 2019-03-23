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
        mainwindow.cpp \
    _aboutdialog.cpp

HEADERS  += mainwindow.h \
    _utility.h \
    _blendSort.h \
    _InsertionSort.h \
    _airplane.h \
    _aboutdialog.h

FORMS    += mainwindow.ui \
    _aboutdialog.ui

RESOURCES += \
    source.qrc

