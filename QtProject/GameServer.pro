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
    ../GameServer/net/callback.h \
    ../GameServer/net/netthread.h \
    ../GameServer/frame/game.h \
    ../GameServer/main/mainthread.h \
    ../GameServer/db/dbthread.h

SOURCES += \
    ../GameServer/net/callback.cpp \
    ../GameServer/net/netthread.cpp \
    ../GameServer/frame/game.cpp \
    ../GameServer/frame/main.cpp \
    ../GameServer/main/mainthread.cpp \
    ../GameServer/db/dbthread.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/linux/release/ -lFrame
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/linux/debug/ -lFrame
else:unix: LIBS += -L$$PWD/../lib/linux/ -lFrame

INCLUDEPATH += $$PWD/../lib/include/frame
DEPENDPATH += $$PWD/../lib/include/frame

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/libFrame.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/libFrame.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/Frame.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/Frame.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/linux/libFrame.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/linux/release/ -lCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/linux/debug/ -lCommon
else:unix: LIBS += -L$$PWD/../lib/linux/ -lCommon

INCLUDEPATH += $$PWD/../lib/include/common
DEPENDPATH += $$PWD/../lib/include/common

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/libCommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/libCommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/Common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/Common.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/linux/libCommon.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/linux/release/ -lThread
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/linux/debug/ -lThread
else:unix: LIBS += -L$$PWD/../lib/linux/ -lThread

INCLUDEPATH += $$PWD/../lib/include/thread
DEPENDPATH += $$PWD/../lib/include/thread

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/libThread.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/libThread.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/Thread.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/Thread.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/linux/libThread.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/linux/release/ -lTinyxml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/linux/debug/ -lTinyxml
else:unix: LIBS += -L$$PWD/../lib/linux/ -lTinyxml

INCLUDEPATH += $$PWD/../lib/include/tinyxml
DEPENDPATH += $$PWD/../lib/include/tinyxml

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/libTinyxml.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/libTinyxml.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/Tinyxml.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/Tinyxml.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/linux/libTinyxml.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/linux/release/ -lTimeManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/linux/debug/ -lTimeManager
else:unix: LIBS += -L$$PWD/../lib/linux/ -lTimeManager

INCLUDEPATH += $$PWD/../lib/include/timemanager
DEPENDPATH += $$PWD/../lib/include/timemanager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/libTimeManager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/libTimeManager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/TimeManager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/TimeManager.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/linux/libTimeManager.a
