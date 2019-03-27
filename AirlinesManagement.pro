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


SOURCES += sources/main.cpp\
        sources/mainwindow.cpp \
    sources/_aboutdialog.cpp \
    sources/_appenddialog.cpp \
    sources/_blendsort.cpp \
    sources/_utility.cpp \
    sources/_Insertionsort.cpp \

HEADERS  += headers/mainwindow.h \
    headers/_airplane.h \
    headers/_aboutdialog.h \
    headers/_appenddialog.h \
    headers/_utility.h \
    headers/_blendSort.h \
    headers/_InsertionSort.h

FORMS    += UIs/mainwindow.ui \
    UIs/_aboutdialog.ui \
    UIs/_appenddialog.ui

RESOURCES += \
    source.qrc

