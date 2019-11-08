#-------------------------------------------------
#
# Project created by QtCreator 2019-11-07T08:26:39
#
#-------------------------------------------------

QT       += core gui svg
CONFIG  += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SvgPlay
TEMPLATE = app

QMAKE_CXXFLAGS += "-Wno-inconsistent-missing-override"


SOURCES += main.cpp\
        mainwindow.cpp \
    keyb-utils.cpp

HEADERS  += mainwindow.h \
    keyb-utils.h

FORMS    += mainwindow.ui
