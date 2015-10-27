#-------------------------------------------------
#
# Project created by QtCreator 2015-08-16T10:23:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cubiectrl-values-display
TEMPLATE = app


SOURCES += main.cpp \
    display.cpp \
    controlsocket.cpp

HEADERS  += \
    display.h \
    controlsocket.h

FORMS    +=

RESOURCES += \
    res.qrc
