
#ifndef DEFINE_H
#define DEFINE_H

typedef short							Int16;
typedef unsigned short					UInt16;
typedef unsigned int					UInt32;
typedef char							GameName[32];
typedef unsigned int					RoleID;
typedef unsigned int					ObjID;
typedef int								SceneID;

static const ObjID	INVALID_OBJ_ID = ObjID(0);
//static const int	GAME_NAME_LEN = sizeof(GameName)/sizeof(char);

struct ThreadMsg
{
	int length;
	char *data;
};

#endif
