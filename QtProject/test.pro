QT += core
QT -= gui

TARGET = Test
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app
INCLUDEPATH = ../ ../Test

SOURCES += \
    ../Test/main.cpp \
    ../Test/testframe.cpp \
    ../common/commonfunction.cpp \
    ../common/globalclass.cpp

HEADERS += \
    ../Test/lua/luatest.h \
    ../Test/other/bridge.h \
    ../Test/other/hashlisttest.h \
    ../Test/other/logtest.h \
    ../Test/websocket/websockettest.h \
    ../Test/testcache.h \
    ../Test/testchrono.h \
    ../Test/testdatastructure.h \
    ../Test/testframe.h \
    ../Test/testlog.h \
    ../Test/testmemory.h \
    ../Test/testmysql.h \
    ../Test/testother.h \
    ../Test/testredis.h \
    ../Test/testserializer.h \
    ../Test/testsocket.h \
    ../Test/testthread.h \
    ../common/datastructure/circlequeue.h \
    ../common/datastructure/gamearray.h \
    ../common/datastructure/gamehash - 副本.h \
    ../common/datastructure/gamehash.h \
    ../common/datastructure/gameheap.h \
    ../common/datastructure/gamelist.h \
    ../common/datastructure/gamemap.h \
    ../common/datastructure/gameset.h \
    ../common/datastructure/gamevector.h \
    ../common/datastructure/gamevector2.h \
    ../common/datastructure/msgqueue.h \
    ../common/datastructure/rbtree - 副本.h \
    ../common/datastructure/rbtree.h \
    ../common/datastructure/sortlist.h \
    ../common/datastructure/sortmap.h \
    ../common/datastructure/vector2d.h \
    ../common/datastructure/webmsgqueue.h \
    ../common/protocol/internaltype.h \
    ../common/protocol/l_dbprotocol.h \
    ../common/protocol/messageheader.h \
    ../common/protocol/messagetype.h \
    ../common/protocol/msgcode.h \
    ../common/protocol/msggame.h \
    ../common/protocol/protocalheader.h \
    ../common/basedef.h \
    ../common/commonfunction.h \
    ../common/commonvariable.h \
    ../common/globalclass.h \
    ../common/serverdef.h \
    ../common/socketdef.h \
    ../common/vector2d.h


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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/linux/release/ -lLog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/linux/debug/ -lLog
else:unix: LIBS += -L$$PWD/../lib/linux/ -lLog

INCLUDEPATH += $$PWD/../lib/include/log
DEPENDPATH += $$PWD/../lib/include/log

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/libLog.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/libLog.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/Log.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/Log.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/linux/libLog.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/linux/release/ -lCache
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/linux/debug/ -lCache
else:unix: LIBS += -L$$PWD/../lib/linux/ -lCache

INCLUDEPATH += $$PWD/../lib/linux
DEPENDPATH += $$PWD/../lib/linux

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/libCache.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/libCache.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/release/Cache.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/linux/debug/Cache.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/linux/libCache.a
