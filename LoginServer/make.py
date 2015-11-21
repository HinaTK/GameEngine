#encoding: utf-8

import os
import os.path
import sys

#sys.exit(0);
#########################################################################################################################
#
#	本脚本的作用是:通过配置必要的信息,用python来生成makefile。（技术支持:www.guimigame.com）
#	@FILENAME 		执行脚本输出makefile文件名
#	@BIN 			生成可执行文件名
#	@SUFFIX 		源文件后缀
#	@ROOTPATH		“根”目录路径（脚本工作目录的上一层）
#	@PWD			当前工作目录
#	@WD 			工作目录，如果程序有多个工作目录请一一用append加上
#	@BINDIR			可执行文件输出目录
#	@OBJDIR			中间文件输出目录
#	@INCROOTPATH	头文件包含路径的“根路径”，方便INCPATH的编写
#	@LIBROOTPATH 	包含库的“根”路径，方便LIBS的编写
#	@INCPATH 		头文件包含路径
#	@SYSLIBS 		包含的系统库
#	@LIBS			编译程序需要包含的库
# 	@CXX			一般填写gcc/g++
#	@FLAGS			gcc/g++的编译标志
#
#########################################################################################################################
FILENAME 	= 'makefile';
BIN			= "LoginServer";
SUFFIX 		= ".cpp";

ROOTPATH 	= os.path.dirname(os.path.dirname(os.path.abspath(__file__)));
PWD 		= os.getcwd();

WD			= [];
WD.append(PWD);
WD.append(ROOTPATH + "/common");


BINDIR		= ROOTPATH + "/LinuxDebug/";
OBJDIR		= BINDIR + "obj/";

INCROOTPATH	= "-I " + ROOTPATH;
LIBROOTPATH = "-L " + ROOTPATH;

INCPATH 	= INCROOTPATH + " " + INCROOTPATH + "/LoginServer";
SYSLIBS		= " -lpthread"
LIBS		= LIBROOTPATH + "/lib/linux " + "-lFrame -lLog -lTimeManager -lCommon -lTinyxml" + SYSLIBS;
CXX			= "g++";
FLAGS		= '-fpermissive -g3 -Wall -std=c++11';

#########################################################################################################################
#
#	以下不需要再配置
#
#########################################################################################################################

OBJFILE		= '';
OBJ2SRC		= [];

SOURCES		= "";

def SearchFiles(path):
	global OBJFILE;
	global OBJ2SRC;
	global SOURCES;
	global SUFFIX;
	listFile = os.listdir(path);
	for file in listFile:
		if os.path.isdir(os.path.join(path, file)):
			SearchFiles(os.path.join(path, file));
		elif file.endswith(SUFFIX) > 0:
			OBJFILE = file;
			OBJFILE = OBJFILE.replace(SUFFIX,'.o');
			OBJ2SRC.append([OBJDIR + OBJFILE,path + "/" + file]);
			SOURCES += path + "/" + file + " ";
		
for dir in WD:
	SearchFiles(dir);

if os.path.exists(FILENAME):
    os.remove(FILENAME);

f = open(FILENAME,'w');

f.write("PWD 				= " + PWD + "\n");
f.write("CXX           		= " + CXX + "\n");
f.write("INCPATH			= " + INCPATH + "\n");
f.write("LIBS 				= " + LIBS + "\n");
f.write("BINDIR				= " + BINDIR +"\n");
f.write("OBJDIR				= " + OBJDIR + "\n");
f.write("BIN 				= " + BIN + "\n");
f.write("SOURCES			= " + SOURCES+ "\n");
f.write("SOURCEFILES		= $(notdir $(SOURCES))\n");
f.write("OBJECTS			= $(addprefix $(OBJDIR), $(patsubst %.cpp,%.o,$(SOURCEFILES)))\n");
f.write("FLAGS				= " + FLAGS + "\n");
f.write("\n");

f.write("all:makedir $(OBJECTS)\n");
f.write("	$(CXX) $(FLAGS) $(INCPATH) -o $(BIN) $(OBJECTS) $(LIBS);\n");
f.write("\n");

f.write("makedir:\n");
f.write('	$(shell if [ -n "$(OBJDIR)" -a ! -e "$(OBJDIR)" ];then mkdir -p $(OBJDIR); fi)\n');
f.write('	$(shell if [ -n "$(BINDIR)" -a ! -e "$(BINDIR)" ];then mkdir -p $(BINDIR); fi)\n');
f.write("\n");	

for val in OBJ2SRC:
	f.write(val[0] + ":" + val[1] +"\n");
	f.write("	rm -f $@\n");
	f.write("	$(CXX) $(FLAGS) -fpic -c $(INCPATH) $< -o $@\n");
	f.write("\n");

f.close();

os.system("make");
os.system("mv " + BIN + " " + BINDIR);
os.system("cd " + OBJDIR + ";rm -f *.o");


