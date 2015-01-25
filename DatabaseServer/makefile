PWD 				= /mnt/hgfs/GameEngine/DatabaseServer
CXX           		= g++
INCPATH			= -I /mnt/hgfs/GameEngine/common -I /mnt/hgfs/GameEngine/lib/include
LIBS 				= -L /mnt/hgfs/GameEngine/lib/linux -lFrame -lServerConfig  -lTimeManager -lCache -lCommon -lTinyxml -lmysqlclient -lpthread
BINDIR				= /mnt/hgfs/GameEngine/LinuxDebug/
OBJDIR				= /mnt/hgfs/GameEngine/LinuxDebug/obj/
BIN 				= DatabaseServer
SOURCES			= /mnt/hgfs/GameEngine/DatabaseServer/cache/testcache.cpp /mnt/hgfs/GameEngine/DatabaseServer/database/database.cpp /mnt/hgfs/GameEngine/DatabaseServer/database/gamemysql.cpp /mnt/hgfs/GameEngine/DatabaseServer/database/gamemysqlstmt.cpp /mnt/hgfs/GameEngine/DatabaseServer/frame/databaseframe.cpp /mnt/hgfs/GameEngine/DatabaseServer/frame/main.cpp /mnt/hgfs/GameEngine/DatabaseServer/msghandler/messagehandler.cpp /mnt/hgfs/GameEngine/DatabaseServer/table/datatable.cpp /mnt/hgfs/GameEngine/DatabaseServer/table/datatablestmt.cpp /mnt/hgfs/GameEngine/DatabaseServer/table/tb_login.cpp /mnt/hgfs/GameEngine/DatabaseServer/table/testtable.cpp /mnt/hgfs/GameEngine/common/commonfunction.cpp 
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))
FLAGS				= -g -Wall

all:makedir $(OBJECTS)
	$(CXX) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS) $(LIBS);

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

/mnt/hgfs/GameEngine/LinuxDebug/obj/testcache.o:/mnt/hgfs/GameEngine/DatabaseServer/cache/testcache.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/database.o:/mnt/hgfs/GameEngine/DatabaseServer/database/database.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/gamemysql.o:/mnt/hgfs/GameEngine/DatabaseServer/database/gamemysql.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/gamemysqlstmt.o:/mnt/hgfs/GameEngine/DatabaseServer/database/gamemysqlstmt.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/databaseframe.o:/mnt/hgfs/GameEngine/DatabaseServer/frame/databaseframe.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/main.o:/mnt/hgfs/GameEngine/DatabaseServer/frame/main.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/messagehandler.o:/mnt/hgfs/GameEngine/DatabaseServer/msghandler/messagehandler.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/datatable.o:/mnt/hgfs/GameEngine/DatabaseServer/table/datatable.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/datatablestmt.o:/mnt/hgfs/GameEngine/DatabaseServer/table/datatablestmt.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/tb_login.o:/mnt/hgfs/GameEngine/DatabaseServer/table/tb_login.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/testtable.o:/mnt/hgfs/GameEngine/DatabaseServer/table/testtable.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/commonfunction.o:/mnt/hgfs/GameEngine/common/commonfunction.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

