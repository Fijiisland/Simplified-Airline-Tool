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
    _aboutdialog.cpp \
    _appenddialog.cpp

HEADERS  += mainwindow.h \
    _airplane.h \
    _aboutdialog.h \
    _appenddialog.h \
    _blendSort.hpp \
    _InsertionSort.hpp \
    _utility.hpp

FORMS    += mainwindow.ui \
    _aboutdialog.ui \
    _appenddialog.ui

RESOURCES += \
    source.qrc

