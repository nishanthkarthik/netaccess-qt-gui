#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T18:35:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = netAccess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    libnetaccess.cpp

HEADERS  += mainwindow.h \
    libnetaccess.h

FORMS    += mainwindow.ui

LIBS    +=  -lcurl

CONFIG += c++11
