#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T10:11:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = Thread
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
INCLUDEPATH = ../../lib/include/ ../../lib/include/thread/ ../../

HEADERS += \
    ../../lib/include/thread/basethread.h \
    ../../lib/include/thread/threadmanager.h

SOURCES += \
    ../../lib/src/thread/basethread.cpp \
    ../../lib/src/thread/threadmanager.cpp

