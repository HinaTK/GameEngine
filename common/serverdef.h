
#ifndef SERVER_DEF_H
#define SERVER_DEF_H

static const int PLAT_NAME_SIZE = 32;
static const int GAME_NAME_SIZE = 32;

typedef unsigned char	Byte;
typedef char			PlatName[PLAT_NAME_SIZE];
typedef char			GameName[GAME_NAME_SIZE];
typedef int				ServerID;
typedef long long		RoleID;
typedef unsigned char	ThreadID;
#endif

