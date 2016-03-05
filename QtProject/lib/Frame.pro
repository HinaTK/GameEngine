#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T10:11:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = Frame
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
INCLUDEPATH = ../../lib/include/ ../../lib/include/frame/ ../../

SOURCES += \
    ../../lib/src/frame/accepter.cpp \
    ../../lib/src/frame/baselistener.cpp \
    ../../lib/src/frame/bufmanager.cpp \
    ../../lib/src/frame/frame.cpp \
    ../../lib/src/frame/listener.cpp \
    ../../lib/src/frame/message.cpp \
    ../../lib/src/frame/msgproxy.cpp \
    ../../lib/src/frame/netcommon.cpp \
    ../../lib/src/frame/nethandler.cpp \
    ../../lib/src/frame/net_base.cpp \
    ../../lib/src/frame/net_unix.cpp

HEADERS += \
    ../../lib/include/frame/accepter.h \
    ../../lib/include/frame/baselistener.h \
    ../../lib/include/frame/bufmanager.h \
    ../../lib/include/frame/excom.h \
    ../../lib/include/frame/frame.h \
    ../../lib/include/frame/listener.h \
    ../../lib/include/frame/message.h \
    ../../lib/include/frame/msgcallback.h \
    ../../lib/include/frame/msgproxy.h \
    ../../lib/include/frame/netcommon.h \
    ../../lib/include/frame/nethandler.h \
    ../../lib/include/frame/netmanager.h \
    ../../lib/include/frame/net_base.h \
    ../../lib/include/frame/net_unix.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
