PWD 				= /mnt/hgfs/GameEngine/Test
CXX           		= g++
INCPATH			= -I /mnt/hgfs/GameEngine -I /mnt/hgfs/GameEngine/lib/include
LIBS 				= -L /mnt/hgfs/GameEngine/lib/linux -lFrame -lLog -lTimeManager -lScript -lCommon -lTinyxml -lmysqlclient -lpthread
BINDIR				= /mnt/hgfs/GameEngine/LinuxDebug/
OBJDIR				= /mnt/hgfs/GameEngine/LinuxDebug/obj/
BIN 				= Test
SOURCES			= /mnt/hgfs/GameEngine/Test/main.cpp /mnt/hgfs/GameEngine/common/commonfunction.cpp /mnt/hgfs/GameEngine/common/datastructure/gamemap.cpp /mnt/hgfs/GameEngine/common/globalclass.cpp 
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))
FLAGS				= -g -Wall

all:makedir $(OBJECTS)
	$(CXX) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS) $(LIBS);

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

/mnt/hgfs/GameEngine/LinuxDebug/obj/main.o:/mnt/hgfs/GameEngine/Test/main.cpp
	rm -f $@
	$(CXX) -fpic -g -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/commonfunction.o:/mnt/hgfs/GameEngine/common/commonfunction.cpp
	rm -f $@
	$(CXX) -fpic -g -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/gamemap.o:/mnt/hgfs/GameEngine/common/datastructure/gamemap.cpp
	rm -f $@
	$(CXX) -fpic -g -c $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/LinuxDebug/obj/globalclass.o:/mnt/hgfs/GameEngine/common/globalclass.cpp
	rm -f $@
	$(CXX) -fpic -g -c $(INCPATH) $< -o $@

