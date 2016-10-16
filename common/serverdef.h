
#ifndef SERVER_DEF_H
#define SERVER_DEF_H

#include <stdint.h>

static const int ACCOUNT_SIZE = 36;
static const int GAME_NAME_SIZE = 32;
static const int SESSION_SIZE = 32;

typedef char			IP[16];
typedef unsigned char	Byte;
typedef char			Account[ACCOUNT_SIZE];
typedef char			GameName[GAME_NAME_SIZE];
typedef char			Session[32];
typedef int				ServerID;
typedef long long		RoleID;
typedef unsigned char	ThreadID;
typedef unsigned short	TPT;		// thread proto type
typedef unsigned char	NetMsgType;
typedef unsigned int	NetHandle;	// 内部网络标识

#define INVALID_THREAD_ID 	255
#define INVALID_NET_HANDLE	4294967295

#endif

