
PWD 			= $(shell pwd)

CC            	= gcc
CXX           	= g++
INCPATH       	= -I$(PWD)/../common -I$(PWD)/../common/libheader
LINK          	= g++
LIBS          	= -L../../lib/linux -lmysqlclient -llua


SRCFILES		= $(shell find $(PWD) -name '*.cpp' 2>/dev/null)
all :
	@echo $(INCPATH);