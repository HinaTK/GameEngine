
PWD 			= $(shell pwd)
ROOTPATH		= $(shell cd ..; pwd)

CXX           	= g++
INCPATH       	= -I$(ROOTPATH)/common -I$(ROOTPATH)/lib/include -I$(ROOTPATH)/lib/include/header
LIBS          	= -L$(ROOTPATH)/lib/linux -llibTimeManager -llibServerConfig -llibGameSocket -llibTinyxml
BINDIR			= $(PWD)/Bin
OBJDIR			= $(BINDIR)/obj/

SOURCES			= $(shell find $(PWD) -name '*.cpp' 2>/dev/null)
SOURCEFILES		= $(notdir $(SOURCES))
OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))

FLAGS			= -g -Wall
all :makedir $(OBJECTS)
	$(CXX) $(LIBS) $(FLAGS) $(INCPATH) -o  $(OBJECTS); 

$(OBJDIR)%.o:$(PWD)/%.cpp
	rm -f $@
	$(CC) -fpic -c $(INCPATH) $< -o $@

makedir:
	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi) 
	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)

clean:
	$(shell cd )
