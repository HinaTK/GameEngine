QT += core
QT -= gui

TARGET = GameServer
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app
INCLUDEPATH = ../ ../GameServer

unix:!macx: LIBS += -L$$PWD/../lib/linux/ -lThread

INCLUDEPATH += $$PWD/../lib/linux
DEPENDPATH += $$PWD/../lib/linux

unix:!macx: PRE_TARGETDEPS += $$PWD/../lib/linux/libThread.a

unix:!macx: LIBS += -L$$PWD/../lib/linux/ -lFrame

INCLUDEPATH += $$PWD/../lib/linux
DEPENDPATH += $$PWD/../lib/linux

unix:!macx: PRE_TARGETDEPS += $$PWD/../lib/linux/libFrame.a

HEADERS += \
    ../GameServer/frame/callback.h \
    ../GameServer/frame/gameframe.h \
    ../GameServer/main/mainthread.h \
    ../GameServer/db/dbthread.h \
    ../common/commonfunction.h

SOURCES += \
    ../GameServer/frame/callback.cpp \
    ../GameServer/frame/gameframe.cpp \
    ../GameServer/frame/main.cpp \
    ../GameServer/main/mainthread.cpp \
    ../GameServer/db/dbthread.cpp \
    ../common/commonfunction.cpp


unix:!macx: LIBS += -L$$PWD/../lib/linux/ -lCommon

INCLUDEPATH += $$PWD/../lib/linux
DEPENDPATH += $$PWD/../lib/linux

unix:!macx: PRE_TARGETDEPS += $$PWD/../lib/linux/libCommon.a

unix:!macx: LIBS += -L$$PWD/../LinuxDebug/ -lTimeManager

INCLUDEPATH += $$PWD/../LinuxDebug
DEPENDPATH += $$PWD/../LinuxDebug

unix:!macx: PRE_TARGETDEPS += $$PWD/../LinuxDebug/libTimeManager.a
