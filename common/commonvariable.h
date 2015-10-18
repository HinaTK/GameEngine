#ifndef COMMON_VARIABLE_H
#define COMMON_VARIABLE_H

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>

/*
	多个server可以共同包含
*/

typedef short							Int16;
typedef unsigned short					UInt16;
typedef unsigned int					UInt32;
typedef char							GameName[32];
typedef unsigned int					RoleID;
typedef unsigned short					ObjID;

static const ObjID	INVALID_OBJ_ID = ObjID(0);
static const int	GAME_NAME_LEN = sizeof(GameName)/sizeof(char);

enum
{
	DATABASE_SERVER,
	LOGIN_SERVER,
	GAME_SERVER,
	GATEWAY_SERVER,
	MAX_SERVER,
};

#endif
