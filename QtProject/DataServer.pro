QT += core
QT -= gui

TARGET = DataServer
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app
INCLUDEPATH = ../ ../DataServer

LIBS += -lmysqlclient

SOURCES += \
    ../DataServer/cache/datamapmanager.cpp \
    ../DataServer/database/database.cpp \
    ../DataServer/database/tablebase.cpp \
    ../DataServer/frame/databaseframe.cpp \
    ../DataServer/frame/main.cpp \
    ../DataServer/message/messagehandler.cpp \
    ../DataServer/table/datatable.cpp \
    ../DataServer/table/datatablestmt.cpp \
    ../DataServer/table/tabledefine.cpp \
    ../DataServer/table/tb_login.cpp \
    ../common/commonfunction.cpp \
    ../common/globalclass.cpp

HEADERS += \
    ../DataServer/cache/datamapmanager.h \
    ../DataServer/database/database.h \
    ../DataServer/database/tablebase.h \
    ../DataServer/database/tableid.h \
    ../DataServer/frame/databaseframe.h \
    ../DataServer/frame/rpc.h \
    ../DataServer/include/mysql/psi/mysql_file.h \
    ../DataServer/include/mysql/psi/mysql_idle.h \
    ../DataServer/include/mysql/psi/mysql_socket.h \
    ../DataServer/include/mysql/psi/mysql_stage.h \
    ../DataServer/include/mysql/psi/mysql_statement.h \
    ../DataServer/include/mysql/psi/mysql_table.h \
    ../DataServer/include/mysql/psi/mysql_thread.h \
    ../DataServer/include/mysql/psi/psi.h \
    ../DataServer/include/mysql/client_authentication.h \
    ../DataServer/include/mysql/client_plugin.h \
    ../DataServer/include/mysql/get_password.h \
    ../DataServer/include/mysql/innodb_priv.h \
    ../DataServer/include/mysql/plugin.h \
    ../DataServer/include/mysql/plugin_audit.h \
    ../DataServer/include/mysql/plugin_auth.h \
    ../DataServer/include/mysql/plugin_auth_common.h \
    ../DataServer/include/mysql/plugin_ftparser.h \
    ../DataServer/include/mysql/plugin_validate_password.h \
    ../DataServer/include/mysql/service_my_plugin_log.h \
    ../DataServer/include/mysql/service_my_snprintf.h \
    ../DataServer/include/mysql/service_mysql_string.h \
    ../DataServer/include/mysql/service_thd_alloc.h \
    ../DataServer/include/mysql/service_thd_wait.h \
    ../DataServer/include/mysql/service_thread_scheduler.h \
    ../DataServer/include/mysql/services.h \
    ../DataServer/include/mysql/thread_pool_priv.h \
    ../DataServer/include/big_endian.h \
    ../DataServer/include/byte_order_generic.h \
    ../DataServer/include/byte_order_generic_x86.h \
    ../DataServer/include/byte_order_generic_x86_64.h \
    ../DataServer/include/decimal.h \
    ../DataServer/include/errmsg.h \
    ../DataServer/include/keycache.h \
    ../DataServer/include/little_endian.h \
    ../DataServer/include/m_ctype.h \
    ../DataServer/include/m_string.h \
    ../DataServer/include/my_alloc.h \
    ../DataServer/include/my_attribute.h \
    ../DataServer/include/my_byteorder.h \
    ../DataServer/include/my_compiler.h \
    ../DataServer/include/my_config.h \
    ../DataServer/include/my_dbug.h \
    ../DataServer/include/my_dir.h \
    ../DataServer/include/my_getopt.h \
    ../DataServer/include/my_global.h \
    ../DataServer/include/my_list.h \
    ../DataServer/include/my_net.h \
    ../DataServer/include/my_pthread.h \
    ../DataServer/include/my_sys.h \
    ../DataServer/include/my_xml.h \
    ../DataServer/include/mysql.h \
    ../DataServer/include/mysql_com.h \
    ../DataServer/include/mysql_com_server.h \
    ../DataServer/include/mysql_embed.h \
    ../DataServer/include/mysql_time.h \
    ../DataServer/include/mysql_version.h \
    ../DataServer/include/mysqld_ername.h \
    ../DataServer/include/mysqld_error.h \
    ../DataServer/include/plugin.h \
    ../DataServer/include/plugin_audit.h \
    ../DataServer/include/plugin_ftparser.h \
    ../DataServer/include/plugin_validate_password.h \
    ../DataServer/include/sql_common.h \
    ../DataServer/include/sql_state.h \
    ../DataServer/include/sslopt-case.h \
    ../DataServer/include/sslopt-longopts.h \
    ../DataServer/include/sslopt-vars.h \
    ../DataServer/include/typelib.h \
    ../DataServer/message/messagehandler.h \
    ../DataServer/message/msgtype.h \
    ../DataServer/protocol/msgheader.h \
    ../DataServer/table/datatable.h \
    ../DataServer/table/datatablestmt.h \
    ../DataServer/table/tabledef.h \
    ../DataServer/table/tabledefine.h \
    ../DataServer/table/tb_login.h \
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
