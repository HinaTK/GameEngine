PWD 				= /home/jiaming/git/GameEngine/DatabaseServer
CXX           		= g++
INCPATH			= -I /home/jiaming/git/GameEngine -I /home/jiaming/git/GameEngine/DatabaseServer
LIBS 				= -L /home/jiaming/git/GameEngine/lib/linux -lFrame -lLog -lTimeManager -lCache -lCommon -lTinyxml -lmysqlclient -lpthread
BINDIR				= /home/jiaming/git/GameEngine/LinuxDebug/
OBJDIR				= /home/jiaming/git/GameEngine/LinuxDebug/obj/
BIN 				= DatabaseServer
SOURCES			= /home/jiaming/git/GameEngine/DatabaseServer/cache/datamapmanager.cpp /home/jiaming/git/GameEngine/DatabaseServer/table/datatablestmt.cpp /home/jiaming/git/GameEngine/DatabaseServer/table/datatable.cpp /home/jiaming/git/GameEngine/DatabaseServer/table/tabledefine.cpp /home/jiaming/git/GameEngine/DatabaseServer/table/tb_login.cpp /home/jiaming/git/GameEngine/DatabaseServer/frame/main.cpp /home/jiaming/git/GameEngine/DatabaseServer/frame/databaseframe.cpp /home/jiaming/git/GameEngine/DatabaseServer/message/messagehandler.cpp /home/jiaming/git/GameEngine/DatabaseServer/database/tablebase.cpp /home/jiaming/git/GameEngine/DatabaseServer/database/database.cpp /home/jiaming/git/GameEngine/common/commonfunction.cpp /home/jiaming/git/GameEngine/common/globalclass.cpp 
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))
FLAGS				= -fpermissive -g3 -Wall -std=c++11

all:makedir $(OBJECTS)
	$(CXX) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS) $(LIBS);

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

/home/jiaming/git/GameEngine/LinuxDebug/obj/datamapmanager.o:/home/jiaming/git/GameEngine/DatabaseServer/cache/datamapmanager.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/datatablestmt.o:/home/jiaming/git/GameEngine/DatabaseServer/table/datatablestmt.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/datatable.o:/home/jiaming/git/GameEngine/DatabaseServer/table/datatable.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/tabledefine.o:/home/jiaming/git/GameEngine/DatabaseServer/table/tabledefine.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/tb_login.o:/home/jiaming/git/GameEngine/DatabaseServer/table/tb_login.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/main.o:/home/jiaming/git/GameEngine/DatabaseServer/frame/main.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/databaseframe.o:/home/jiaming/git/GameEngine/DatabaseServer/frame/databaseframe.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/messagehandler.o:/home/jiaming/git/GameEngine/DatabaseServer/message/messagehandler.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/tablebase.o:/home/jiaming/git/GameEngine/DatabaseServer/database/tablebase.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/database.o:/home/jiaming/git/GameEngine/DatabaseServer/database/database.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/commonfunction.o:/home/jiaming/git/GameEngine/common/commonfunction.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/globalclass.o:/home/jiaming/git/GameEngine/common/globalclass.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

