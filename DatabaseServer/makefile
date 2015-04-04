PWD 				= /mnt/hgfs/GameEngine/DatabaseServer
CXX           		= g++
INCPATH			= -I /mnt/hgfs/GameEngine -I /mnt/hgfs/GameEngine/DatabaseServer
LIBS 				= -L /mnt/hgfs/GameEngine/lib/linux -lFrame -lLog -lTimeManager -lCache -lCommon -lTinyxml -lmysqlclient -lpthread
BINDIR				= /mnt/hgfs/GameEngine/LinuxDebug/
OBJDIR				= /mnt/hgfs/GameEngine/LinuxDebug/obj/
BIN 				= DatabaseServer
SOURCES			= /mnt/hgfs/GameEngine/DatabaseServer/cache/datamapmanager.cpp /mnt/hgfs/GameEngine/DatabaseServer/database/database.cpp /mnt/hgfs/GameEngine/DatabaseServer/database/tablebase.cpp /mnt/hgfs/GameEngine/DatabaseServer/frame/databaseframe.cpp /mnt/hgfs/GameEngine/DatabaseServer/frame/main.cpp /mnt/hgfs/GameEngine/DatabaseServer/message/messagehandler.cpp /mnt/hgfs/GameEngine/DatabaseServer/table/datatable.cpp /mnt/hgfs/GameEngine/DatabaseServer/table/datatablestmt.cpp /mnt/hgfs/GameEngine/DatabaseServer/table/tb_login.cpp /mnt/hgfs/GameEngine/common/commonfunction.cpp /mnt/hgfs/GameEngine/common/globalclass.cpp 
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))
FLAGS				= -fpermissive -g3 -Wall

all:makedir $(OBJECTS)
	$(CXX) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS) $(LIBS);

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

/mnt/hgfs/GameEngine/LinuxDebug/obj/datamapmanager.o:/mnt/hgfs/GameEngine/DatabaseServer/cache/datamapmanager.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/database.o:/mnt/hgfs/GameEngine/DatabaseServer/database/database.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/tablebase.o:/mnt/hgfs/GameEngine/DatabaseServer/database/tablebase.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/databaseframe.o:/mnt/hgfs/GameEngine/DatabaseServer/frame/databaseframe.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/main.o:/mnt/hgfs/GameEngine/DatabaseServer/frame/main.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/messagehandler.o:/mnt/hgfs/GameEngine/DatabaseServer/message/messagehandler.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/datatable.o:/mnt/hgfs/GameEngine/DatabaseServer/table/datatable.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/datatablestmt.o:/mnt/hgfs/GameEngine/DatabaseServer/table/datatablestmt.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/tb_login.o:/mnt/hgfs/GameEngine/DatabaseServer/table/tb_login.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/commonfunction.o:/mnt/hgfs/GameEngine/common/commonfunction.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/globalclass.o:/mnt/hgfs/GameEngine/common/globalclass.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

