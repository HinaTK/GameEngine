
#ifndef NET_COMMON_H
#define NET_COMMON_H

#include <string>
#include "export.h"
#include "common/socketdef.h"

namespace NetCommon
{
	EXPORT bool		Init(const char *ip, unsigned short port, int backlog, SOCKET &sock);
	EXPORT SOCKET	Connect(const char *ip, unsigned short port);

	EXPORT int		StartUp();

	EXPORT int		CleanUp();

	EXPORT int		Send(SOCKET sock, const char *msg, unsigned int length);

	EXPORT void		Close(SOCKET sock);

	EXPORT int		Ioctl(SOCKET sock, long cmd, unsigned long *argp);

	// 设置套接字参数
	EXPORT int		SetSockopt(SOCKET sock, int level, int optname, const char *optval, int optlen);

	// 获取错误信息
	EXPORT int		Error(void);

	// 协议头
	struct Header
	{
		int	msg_len;		// 消息长度
	};

	static const int HEADER_LENGTH = sizeof(Header);

	struct GateHeader
	{
		int			msg_len;
		NetHandle	handle;		// 玩家连到gate的句柄
	};

	static const int GATE_HEADER_LENGTH = sizeof(GateHeader);

	static const int MAX_SERVER_NUM = 32;

	struct ErrInfo
	{
		int err;
		int reason;
	};
// 	struct HandShakeInfo
// 	{
// 		std::string header;
// 		std::string key;
// 		std::string magic_key;
// 		std::string handshake;
// 	};
// 
// 	HandShakeInfo ws;
// 	std::string ws_header;
// 	std::string ws_key;
// 	std::string ws_magic_key;
// 	std::string ws_handshake;

//	ws_header = "Sec-WebSocket-Version:";
// 	m_handshake += "Upgrade: WebSocket\r\n";
// 	m_handshake += "Connection: Upgrade\r\n";
// 	m_handshake += "Sec-WebSocket-Accept: %s\r\n";
// 	m_handshake += "\r\n";
}

//void	

#endif