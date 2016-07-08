#-------------------------------------------------
#
# Project created by QtCreator 2016-07-02T00:26:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = heroes_server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    unit.cpp \
    troop.cpp \
    field.cpp \
    session.cpp

HEADERS  += mainwindow.h \
    unit.h \
    troop.h \
    field.h \
    session.h

FORMS    += mainwindow.ui
