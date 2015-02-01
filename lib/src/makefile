PWD 				= /mnt/hgfs/GameEngine/lib/src
AR           		= ar cqs
CXX           		= g++
INCPATH			= -I /mnt/hgfs/GameEngine/lib/../ -I /mnt/hgfs/GameEngine/lib/include -I /mnt/hgfs/GameEngine/lib/include/timemanager
BINDIR				= /mnt/hgfs/GameEngine/lib/linux/
OBJDIR				= /mnt/hgfs/GameEngine/lib/linux/obj/
BIN 				= libTimeManager.a
SOURCES			= /mnt/hgfs/GameEngine/lib/src/timemanager/gametime.cpp /mnt/hgfs/GameEngine/lib/src/timemanager/timemanager.cpp 
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))
FLAGS				= -fpic -g -c

all:makedir $(OBJECTS)
	$(AR) $(BIN) $(OBJECTS);

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

/mnt/hgfs/GameEngine/lib/linux/obj/gametime.o:/mnt/hgfs/GameEngine/lib/src/timemanager/gametime.cpp
	rm -f $@
	$(CXX) $(FLAGS) $(INCPATH) $< -o $@

/mnt/hgfs/GameEngine/lib/linux/obj/timemanager.o:/mnt/hgfs/GameEngine/lib/src/timemanager/timemanager.cpp
	rm -f $@
	$(CXX) $(FLAGS) $(INCPATH) $< -o $@

