
#ifndef SOCKET_DEF_H
#define SOCKET_DEF_H

#ifdef WIN32
#define SOCKET_LEN		int
#define WOULDBLOCK		WSAEWOULDBLOCK
#endif // !WIN32


#ifdef __unix
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define SOCKET_LEN		socklen_t
#define INVALID_SOCKET	-1
#define WOULDBLOCK		EWOULDBLOCK
#define SOCKET_ERROR	-1
#define SOCKET			int
#endif

#endif