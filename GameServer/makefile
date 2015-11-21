PWD 				= /home/jiaming/git/GameEngine/GameServer
CXX           		= g++
INCPATH			= -I /home/jiaming/git/GameEngine -I /home/jiaming/git/GameEngine/GameServer 
LIBS 				= -L /home/jiaming/git/GameEngine/lib/linux -lFrame -lTimeManager -lCommon -lTinyxml -lpthread
BINDIR				= /home/jiaming/git/GameEngine/LinuxDebug/
OBJDIR				= /home/jiaming/git/GameEngine/LinuxDebug/obj/
BIN 				= GameServer
SOURCES			= /home/jiaming/git/GameEngine/GameServer/poolconfig/test.cpp /home/jiaming/git/GameEngine/GameServer/poolconfig/memorypoolconfig.cpp /home/jiaming/git/GameEngine/GameServer/frame/main.cpp /home/jiaming/git/GameEngine/GameServer/frame/gamethread.cpp /home/jiaming/git/GameEngine/GameServer/frame/gameframe.cpp /home/jiaming/git/GameEngine/GameServer/base/knapsack.cpp /home/jiaming/git/GameEngine/GameServer/global/globalfunction.cpp /home/jiaming/git/GameEngine/GameServer/obj/obj.cpp /home/jiaming/git/GameEngine/GameServer/obj/role.cpp /home/jiaming/git/GameEngine/GameServer/obj/objmanager.cpp /home/jiaming/git/GameEngine/GameServer/scene/observer.cpp /home/jiaming/git/GameEngine/GameServer/scene/area.cpp /home/jiaming/git/GameEngine/GameServer/scene/aoi.cpp /home/jiaming/git/GameEngine/GameServer/scene/areamanager.cpp /home/jiaming/git/GameEngine/GameServer/scene/scenemanager.cpp /home/jiaming/git/GameEngine/GameServer/scene/scene.cpp /home/jiaming/git/GameEngine/GameServer/message/messagefunction/messagehandler.cpp /home/jiaming/git/GameEngine/GameServer/other/showcrash.cpp /home/jiaming/git/GameEngine/GameServer/other/log.cpp /home/jiaming/git/GameEngine/GameServer/other/MyDll.cpp /home/jiaming/git/GameEngine/GameServer/other/dll.cpp /home/jiaming/git/GameEngine/common/commonfunction.cpp /home/jiaming/git/GameEngine/common/globalclass.cpp 
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))
FLAGS				= -fpermissive -g3 -Wall -std=c++11

all:makedir $(OBJECTS)
	$(CXX) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS) $(LIBS);

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

/home/jiaming/git/GameEngine/LinuxDebug/obj/test.o:/home/jiaming/git/GameEngine/GameServer/poolconfig/test.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/memorypoolconfig.o:/home/jiaming/git/GameEngine/GameServer/poolconfig/memorypoolconfig.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/main.o:/home/jiaming/git/GameEngine/GameServer/frame/main.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/gamethread.o:/home/jiaming/git/GameEngine/GameServer/frame/gamethread.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/gameframe.o:/home/jiaming/git/GameEngine/GameServer/frame/gameframe.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/knapsack.o:/home/jiaming/git/GameEngine/GameServer/base/knapsack.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/globalfunction.o:/home/jiaming/git/GameEngine/GameServer/global/globalfunction.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/obj.o:/home/jiaming/git/GameEngine/GameServer/obj/obj.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/role.o:/home/jiaming/git/GameEngine/GameServer/obj/role.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/objmanager.o:/home/jiaming/git/GameEngine/GameServer/obj/objmanager.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/observer.o:/home/jiaming/git/GameEngine/GameServer/scene/observer.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/area.o:/home/jiaming/git/GameEngine/GameServer/scene/area.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/aoi.o:/home/jiaming/git/GameEngine/GameServer/scene/aoi.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/areamanager.o:/home/jiaming/git/GameEngine/GameServer/scene/areamanager.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/scenemanager.o:/home/jiaming/git/GameEngine/GameServer/scene/scenemanager.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/scene.o:/home/jiaming/git/GameEngine/GameServer/scene/scene.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/messagehandler.o:/home/jiaming/git/GameEngine/GameServer/message/messagefunction/messagehandler.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/showcrash.o:/home/jiaming/git/GameEngine/GameServer/other/showcrash.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/log.o:/home/jiaming/git/GameEngine/GameServer/other/log.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/MyDll.o:/home/jiaming/git/GameEngine/GameServer/other/MyDll.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/dll.o:/home/jiaming/git/GameEngine/GameServer/other/dll.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/commonfunction.o:/home/jiaming/git/GameEngine/common/commonfunction.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/globalclass.o:/home/jiaming/git/GameEngine/common/globalclass.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

