#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T10:11:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = TimeManager
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
INCLUDEPATH = ../../lib/include/ ../../lib/include/timemanager/ ../../

HEADERS += \
    ../../lib/include/timemanager/gametime.h \
    ../../lib/include/timemanager/timemanager.h

SOURCES += \
    ../../lib/src/timemanager/gametime.cpp \
    ../../lib/src/timemanager/timemanager.cpp

