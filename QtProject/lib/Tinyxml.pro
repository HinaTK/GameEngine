#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T10:11:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = Tinyxml
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
INCLUDEPATH = ../../lib/include/ ../../lib/include/common/ ../../

SOURCES += \
    ../../lib/src/tinyxml/tinystr.cpp \
    ../../lib/src/tinyxml/tinyxml.cpp \
    ../../lib/src/tinyxml/tinyxmlerror.cpp \
    ../../lib/src/tinyxml/tinyxmlparser.cpp

HEADERS += \
    ../../lib/include/tinyxml/tinystr.h \
    ../../lib/include/tinyxml/tinyxml.h \
    ../../lib/src/tinyxml/tinystr.h \
    ../../lib/src/tinyxml/tinyxml.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
