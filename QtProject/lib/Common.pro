#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T10:11:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = Common
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
INCLUDEPATH = ../../lib/include/ ../../lib/include/common/ ../../

SOURCES += \
    ../../lib/src/common/md5.cpp \
    ../../lib/src/common/mem.cpp \
    ../../lib/src/common/memorypool.cpp \
    ../../lib/src/common/memoryvl.cpp \
    ../../lib/src/common/serializer.cpp \
    ../../lib/src/common/serverconfig.cpp \
    ../../lib/src/common/thread.cpp \
    ../../lib/src/common/function.cpp

HEADERS += \
    ../../lib/include/common/md5.h \
    ../../lib/include/common/mem.h \
    ../../lib/include/common/memorypool.h \
    ../../lib/include/common/memoryvl.h \
    ../../lib/include/common/mutex.h \
    ../../lib/include/common/serializer.h \
    ../../lib/include/common/serverconfig.h \
    ../../lib/include/common/thread.h \
    ../../lib/include/common/function.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
