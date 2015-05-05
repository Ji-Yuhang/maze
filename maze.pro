#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T13:29:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = maze
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mazeview.cpp \
    role.cpp \
    obstacle.cpp \
    wall.cpp

HEADERS  += mainwindow.h \
    mazeview.h \
    role.h \
    obstacle.h \
    wall.h

FORMS    += mainwindow.ui
