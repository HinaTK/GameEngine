
#ifndef SERVER_DEF_H
#define SERVER_DEF_H

static const int ACCOUNT_SIZE = 36;
static const int GAME_NAME_SIZE = 32;

typedef unsigned char	Byte;
typedef char			Account[ACCOUNT_SIZE];
typedef char			GameName[GAME_NAME_SIZE];
typedef int				ServerID;
typedef long long		RoleID;
typedef unsigned char	ThreadID;


#define INVALID_THREAD_ID 255

#endif

