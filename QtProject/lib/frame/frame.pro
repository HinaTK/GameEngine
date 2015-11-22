#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T10:11:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = frame
TEMPLATE = lib
CONFIG += staticlib

SOURCES += frame.cpp

HEADERS += frame.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
