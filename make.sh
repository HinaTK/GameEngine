#!/bin/sh
#注意用 sh make.sh

PWD=`pwd`;
#cd ..
#ROOTPATH=`pwd`;
ROOTPATH=${PWD%/*};

BINDIR=$PWD/Bin;
OBJDIR=$BINDIR/obj/;

SOURCES=`find ${PWD} -name '*.cpp' 2>/dev/null`;
SOURCEFILES=${SOURCES##*/}

echo $SOURCES;

file='jiaming';

echo 'PWD 			= $(shell pwd)' >> $file;
echo 'ROOTPATH			= $(shell cd ..; pwd)' >> $file;

echo 'CXX           		= g++' >> $file;
echo 'INCPATH       		= ' >> $file;
echo 'LIBS          		= ' >> $file;
echo 'BINDIR			= $(PWD)/Bin' >> $file;
echo 'OBJDIR			= $(BINDIR)/obj/' >> $file;

echo 'SOURCES			= $(shell find $(PWD) -name '*.cpp' 2>/dev/null)' >> $file;
echo 'SOURCEFILES		= $(notdir $(SOURCES))' >> $file;
echo 'OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))' >> $file;

echo 'FLAGS			= -g -pipe' >> $file;
echo 'BIN			= main' >> $file;

echo 'all :	pre_command $(OBJECTS)' >> $file;
echo '	$(CXX) $(LIBS) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS)' >> $file;


