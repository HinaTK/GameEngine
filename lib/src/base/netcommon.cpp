
#include <memory.h>
#include <stdio.h>
#include "netcommon.h"
#include "common/socketdef.h"
#include "function.h"

namespace NetCommon
{
// ws_header = "Sec-WebSocket-Version:";
// ws_key = "Sec-WebSocket-Key: ";
// ws_magic_key = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
// ws_handshake = "HTTP/1.1 101 Switching Protocols\r\n";

bool Init(const char *ip, unsigned short port, int backlog, SOCKET &sock)
{
	static SOCKET_LEN len = sizeof(struct sockaddr);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sock)
	{
		return false;
	}

	unsigned long enable = 1;
	if (SOCKET_ERROR == SetSockopt(sock, SOL_SOCKET, SO_LINGER, (const char*)&enable, sizeof(unsigned long)))
	{
		Close(sock);
		return false;
	}

	sockaddr_in sa;
	memset(&sa, 0, sizeof(sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	if (ip[0] != '0')
	{
		sa.sin_addr.s_addr = inet_addr(ip);
	}
	else
	{
		sa.sin_addr.s_addr = htonl(INADDR_ANY);
		ip = inet_ntoa(sa.sin_addr);
	}
	
	if (bind(sock, (struct sockaddr *)&sa, len) == SOCKET_ERROR || listen(sock, backlog) == SOCKET_ERROR)
	{
		Close(sock);
		return false;
	}

	return true;
}

SOCKET Connect(const char *ip, unsigned short port)
{
	NetCommon::StartUp();
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		NetCommon::CleanUp();
		Function::Info("Connect Server ip=%s, port=%d init socket fail", ip, port);
		return INVALID_SOCKET;
	}

	if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		Function::Info("Connect Server ip=%s, port=%d fail %d", ip, port, NetCommon::Error());
		NetCommon::Close(sock);
		NetCommon::CleanUp();
		return INVALID_SOCKET;
	}

	Function::Info("Connect Server ip=%s, port=%d Success", ip, port);
	return sock;
}

int StartUp()
{
#if (defined _WIN32) || (defined _WIN64)
	WSAData wsaData;
	return WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif // WIN32
	return 0;
}

int CleanUp()
{
#if (defined _WIN32) || (defined _WIN64)
	return WSACleanup();
#endif
	return 0;
}

int Send(SOCKET sock, const char *msg, unsigned int length)
{
	// 在send 返回 -1并且错误码是 (windows WSAEWOULDBLOCK)、(linux EWOULDBLOCK),表示缓冲区已满
	return send(sock, msg, length, 0);
}


void Close(SOCKET sock)
{
#if (defined _WIN32) || (defined _WIN64)
	closesocket(sock);
#endif // WIN32
#ifdef _unix
	close(sock);
#endif // _unix
}

int Ioctl(SOCKET sock, long cmd, unsigned long *arg)
{
#if (defined _WIN32) || (defined _WIN64)
	return ioctlsocket(sock, cmd, arg);
#endif
#ifdef __unix
	return ioctl(sock, cmd, arg);
#endif
}

int SetSockopt(SOCKET sock, int level, int optname, const char *optval, int optlen)
{
	return setsockopt(sock, level, optname, optval, optlen);
}

int Error(void)
{
#if (defined _WIN32) || (defined _WIN64)
	return (int)WSAGetLastError();
#endif
#ifdef __unix
	return errno;
#endif
}

}