PWD 				= /home/jiaming/git/GameEngine/LoginServer
CXX           		= g++
INCPATH			= -I /home/jiaming/git/GameEngine -I /home/jiaming/git/GameEngine/LoginServer
LIBS 				= -L /home/jiaming/git/GameEngine/lib/linux -lFrame -lLog -lTimeManager -lCommon -lTinyxml -lpthread
BINDIR				= /home/jiaming/git/GameEngine/LinuxDebug/
OBJDIR				= /home/jiaming/git/GameEngine/LinuxDebug/obj/
BIN 				= LoginServer
SOURCES			= /home/jiaming/git/GameEngine/LoginServer/frame/main.cpp /home/jiaming/git/GameEngine/LoginServer/frame/loginframe.cpp /home/jiaming/git/GameEngine/LoginServer/message/messagefunction/messagehandler.cpp /home/jiaming/git/GameEngine/common/commonfunction.cpp /home/jiaming/git/GameEngine/common/globalclass.cpp 
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))
FLAGS				= -fpermissive -g3 -Wall -std=c++11

all:makedir $(OBJECTS)
	$(CXX) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS) $(LIBS);

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

/home/jiaming/git/GameEngine/LinuxDebug/obj/main.o:/home/jiaming/git/GameEngine/LoginServer/frame/main.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/loginframe.o:/home/jiaming/git/GameEngine/LoginServer/frame/loginframe.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/messagehandler.o:/home/jiaming/git/GameEngine/LoginServer/message/messagefunction/messagehandler.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/commonfunction.o:/home/jiaming/git/GameEngine/common/commonfunction.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

/home/jiaming/git/GameEngine/LinuxDebug/obj/globalclass.o:/home/jiaming/git/GameEngine/common/globalclass.cpp
	rm -f $@
	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@

