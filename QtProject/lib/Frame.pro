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
    ../../lib/src/frame/websocket/base64.cpp \
    ../../lib/src/frame/websocket/dataframeheader.cpp \
    ../../lib/src/frame/websocket/sha1.cpp \
    ../../lib/src/frame/accepter.cpp \
    ../../lib/src/frame/baselistener.cpp \
    ../../lib/src/frame/bufmanager.cpp \
    ../../lib/src/frame/frame.cpp \
    ../../lib/src/frame/handshaker.cpp \
    ../../lib/src/frame/listener.cpp \
    ../../lib/src/frame/message.cpp \
    ../../lib/src/frame/msgproxy.cpp \
    ../../lib/src/frame/netcommon.cpp \
    ../../lib/src/frame/nethandler.cpp \
    ../../lib/src/frame/netmanager.cpp \
    ../../lib/src/frame/webaccepter.cpp \
    ../../lib/src/frame/weblistener.cpp

HEADERS += \
    ../../lib/include/frame/websocket/base64.h \
    ../../lib/include/frame/websocket/dataframeheader.h \
    ../../lib/include/frame/websocket/sha1.h \
    ../../lib/include/frame/accepter.h \
    ../../lib/include/frame/baselistener.h \
    ../../lib/include/frame/bufmanager.h \
    ../../lib/include/frame/excom.h \
    ../../lib/include/frame/frame.h \
    ../../lib/include/frame/handshaker.h \
    ../../lib/include/frame/listener.h \
    ../../lib/include/frame/message.h \
    ../../lib/include/frame/msgcallback.h \
    ../../lib/include/frame/msgproxy.h \
    ../../lib/include/frame/netcommon.h \
    ../../lib/include/frame/nethandler.h \
    ../../lib/include/frame/netmanager.h \
    ../../lib/include/frame/webaccepter.h \
    ../../lib/include/frame/weblistener.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
