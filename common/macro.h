
#ifndef MACRO_H
#define MACRO_H

typedef unsigned short Router;

#define BindProto(STRUCT, ID)\
	STRUCT() :router(ID){}\
	unsigned short router;

#endif