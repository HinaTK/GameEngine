
#include "common/socketdef.h"
#include <memory.h>
#include <stdio.h>
#include "netcommon.h"

namespace NetCommon
{
// ws_header = "Sec-WebSocket-Version:";
// ws_key = "Sec-WebSocket-Key: ";
// ws_magic_key = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
// ws_handshake = "HTTP/1.1 101 Switching Protocols\r\n";

bool Init(char *ip, unsigned short port, int backlog, NetID &net_id)
{
	static SOCKET_LEN len = sizeof(struct sockaddr);
	net_id = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == net_id)
	{
		return false;
	}

	sockaddr_in sa;
	memset(&sa, 0, sizeof(sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = inet_addr(ip);

	int ret = bind(net_id, (struct sockaddr *)&sa, len);
	if (SOCKET_ERROR == ret)
	{
		return false;
	}

	ret = listen(net_id, backlog);
	if (SOCKET_ERROR == ret)
	{
		return false;
	}
	return true;
}

int StartUp()
{
#ifdef WIN32
	WSAData wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	return WSAStartup(wVersion, &wsaData);
#endif // WIN32
	return 0;
}

int Send(NetID net_id, const char *msg, unsigned int length)
{
	// 在send 返回 -1并且错误码是 (windows WSAEWOULDBLOCK)、(linux EWOULDBLOCK),表示缓冲区已满
	return send(net_id, msg, length, 0);
}


void Close(NetID net_id)
{
#ifdef WIN32
	closesocket(net_id);
	printf("close = %d\n", net_id);
#endif // WIN32
#ifdef _unix
	close(net_id);
#endif // _unix
}

int Ioctl(NetID net_id, long cmd, unsigned long *arg)
{
#ifdef WIN32
	return ioctlsocket(net_id, cmd, arg);
#endif
#ifdef __unix
	return ioctl(net_id, cmd, arg);
#endif
}

int Error(void)
{
#ifdef WIN32
	return (int)WSAGetLastError();
#endif
#ifdef __unix
	return errno;
#endif
}

}