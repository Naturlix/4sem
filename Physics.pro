#-------------------------------------------------
#
# Project created by QtCreator 2016-04-10T04:58:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Physics
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    object.cpp \
    rectangle.cpp \
    triangle.cpp \
    circle.cpp \
    list.cpp \
    geometry.cpp

HEADERS  += widget.h \
    object.h \
    rectangle.h \
    triangle.h \
    circle.h \
    list.h

FORMS    += widget.ui
