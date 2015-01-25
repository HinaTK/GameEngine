import os
import os.path
import sys

#sys.exit(0);
FILENAME 	= 'test.txt';

PWD 		= os.getcwd();
BINDIR		= PWD + "/Bin";
OBJDIR		= BINDIR + "/obj/";


INCPATH 	= "1234";
LIBS		= "";
CXX			= "g++";
FLAGS		= '-g';

if os.path.exists(FILENAME):
    os.remove(FILENAME);

f = open(FILENAME,'w');

f.write("PWD 				= " + PWD + "\n");
f.write("ROOTPATH			= $(shell cd ..; pwd)\n");
f.write("CXX           		= " + CXX + "\n");
f.write("INCPATH			= " + INCPATH + "\n");
f.write("LIBS 				= " + LIBS + "\n");
f.write("BINDIR				= " + BINDIR +"\n");
f.write("OBJDIR				= " + OBJDIR + "\n");
f.write("SOURCES			= $(shell find $(PWD) -name '*.cpp' 2>/dev/null)\n");
f.write("SOURCEFILES		= $(notdir $(SOURCES))\n");
f.write("OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))\n");
f.write("FLAGS				= " + FLAGS + "\n");
f.write("\n");

f.write("all:pre_command $(OBJECTS)\n");
f.write("	$(CXX) $(LIBS) $(FLAGS) $(INCPATH) -o  $(OBJECTS);\n");
f.write("\n");

f.write("pre_command:\n");
f.write('	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)\n');
f.write('	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)\n');
f.write("\n");

OBJFILE		= '';
OBJ2SRC		= [];

def FindFiles(path):
	global OBJFILE;
	global OBJ2SRC;
	listFile = os.listdir(path);
	for file in listFile:
		if os.path.isdir(file):
			FindFiles(os.path.join(path, file));
		elif file.find(".cpp") > 0:
			OBJFILE = file;
			OBJFILE = OBJFILE.replace('.cpp','.o');
			OBJ2SRC.append([OBJDIR + OBJFILE,path + file]);
		
FindFiles(PWD);

for val in OBJ2SRC:
	f.write(val[0] + ":" + val[1] +"\n");
	f.write("	rm -f $@\n");
	f.write("	$(CC) -fpic -c $(INCPATH) $< -o $@\n");
	f.write("\n");

#print(OBJ2SRC);
f.close();















