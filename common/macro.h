
#ifndef MACRO_H
#define MACRO_H


#define BindProto(STRUCT, ID)\
	STRUCT() :router(ID){}\
	unsigned short router;

#endif