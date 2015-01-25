PWD 				= /mnt/hgfs/GameEngine/GameServer
CXX           		= g++
INCPATH			= -I /mnt/hgfs/GameEngine/GameServer -I /mnt/hgfs/GameEngine/common -I /mnt/hgfs/GameEngine/lib/include
LIBS 				= -L /mnt/hgfs/GameEngine/lib/linux -lFrame -lServerConfig  -lTimeManager -lCommon -lTinyxml -lmysqlclient -lpthread
BINDIR				= /mnt/hgfs/GameEngine/LinuxDebug/
OBJDIR				= /mnt/hgfs/GameEngine/GameServer/obj/
BIN 				= GameServer
SOURCES			= /mnt/hgfs/GameEngine/GameServer/frame/gameframe.cpp /mnt/hgfs/GameEngine/GameServer/frame/main.cpp /mnt/hgfs/GameEngine/GameServer/global/globalfunction.cpp /mnt/hgfs/GameEngine/GameServer/message/messagefunction/messagehandler.cpp /mnt/hgfs/GameEngine/GameServer/obj/obj.cpp /mnt/hgfs/GameEngine/GameServer/obj/objmanager.cpp /mnt/hgfs/GameEngine/GameServer/obj/role.cpp /mnt/hgfs/GameEngine/GameServer/other/dll.cpp /mnt/hgfs/GameEngine/GameServer/other/log.cpp /mnt/hgfs/GameEngine/GameServer/other/MyDll.cpp /mnt/hgfs/GameEngine/GameServer/other/showcrash.cpp /mnt/hgfs/GameEngine/GameServer/poolconfig/memorypoolconfig.cpp /mnt/hgfs/GameEngine/GameServer/poolconfig/test.cpp /mnt/hgfs/GameEngine/GameServer/scene/aoi.cpp /mnt/hgfs/GameEngine/GameServer/scene/area.cpp /mnt/hgfs/GameEngine/GameServer/scene/areamanager.cpp /mnt/hgfs/GameEngine/GameServer/scene/observer.cpp /mnt/hgfs/GameEngine/GameServer/scene/scene.cpp /mnt/hgfs/GameEngine/GameServer/scene/scenemanager.cpp /mnt/hgfs/GameEngine/common/commonfunction.cpp 
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))
FLAGS				= -g -Wall

all:makedir $(OBJECTS)
	$(CXX) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS) $(LIBS);

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

/mnt/hgfs/GameEngine/GameServer/obj/gameframe.o:/mnt/hgfs/GameEngine/GameServer/frame/gameframe.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/main.o:/mnt/hgfs/GameEngine/GameServer/frame/main.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/globalfunction.o:/mnt/hgfs/GameEngine/GameServer/global/globalfunction.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/messagehandler.o:/mnt/hgfs/GameEngine/GameServer/message/messagefunction/messagehandler.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/obj.o:/mnt/hgfs/GameEngine/GameServer/obj/obj.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/objmanager.o:/mnt/hgfs/GameEngine/GameServer/obj/objmanager.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/role.o:/mnt/hgfs/GameEngine/GameServer/obj/role.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/dll.o:/mnt/hgfs/GameEngine/GameServer/other/dll.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/log.o:/mnt/hgfs/GameEngine/GameServer/other/log.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/MyDll.o:/mnt/hgfs/GameEngine/GameServer/other/MyDll.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/showcrash.o:/mnt/hgfs/GameEngine/GameServer/other/showcrash.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/memorypoolconfig.o:/mnt/hgfs/GameEngine/GameServer/poolconfig/memorypoolconfig.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/test.o:/mnt/hgfs/GameEngine/GameServer/poolconfig/test.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/aoi.o:/mnt/hgfs/GameEngine/GameServer/scene/aoi.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/area.o:/mnt/hgfs/GameEngine/GameServer/scene/area.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/areamanager.o:/mnt/hgfs/GameEngine/GameServer/scene/areamanager.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/observer.o:/mnt/hgfs/GameEngine/GameServer/scene/observer.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/scene.o:/mnt/hgfs/GameEngine/GameServer/scene/scene.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/scenemanager.o:/mnt/hgfs/GameEngine/GameServer/scene/scenemanager.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/GameServer/obj/commonfunction.o:/mnt/hgfs/GameEngine/common/commonfunction.cpp
	rm -f $@
	$(CXX) -fpic -c $(INCPATH) $< -o $@

