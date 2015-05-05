
#ifndef SYSTEM_DEF_H
#define SYSTEM_DEF_H

#ifdef WIN32
	#ifdef FD_SETSIZE
		#undef FD_SETSIZE
	#endif
	#define FD_SETSIZE		4096
	#include <winsock2.h>
	#pragma comment(lib,"ws2_32.lib")
	#include <Windows.h>
#endif

#ifdef __unix
#include <unistd.h>
#endif // __unix


#define MAX_EXTERNAL_BUF	4096
#define MAX_INTERNAL_BUF	4096
#define MAX_EPOLL_SIZE		8192

static const int RECV_BUF_SIZE = 64 * 1024; // 64K

#ifdef __unix
typedef int				SOCKET;

#endif

typedef char			IP[64];
typedef unsigned int	NetHandle;	// 内部网络标识

#endif // !WINDOWSDEF_H
