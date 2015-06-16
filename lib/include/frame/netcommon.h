
#ifndef NET_COMMON_H
#define NET_COMMON_H

#include <string>
#include "common/socketdef.h"

namespace NetCommon
{
	bool	Init(char *ip, unsigned short port, int backlog, SOCKET &sock);

	int		StartUp();

	int		CleanUp();

	int		Send(SOCKET sock, const char *msg, unsigned int length);

	void	Close(SOCKET sock);

	int		Ioctl(SOCKET sock, long cmd, unsigned long *argp);

	// �����׽��ֲ���
	int		SetSockopt(SOCKET sock, int level, int optname, const char *optval, int optlen);

	// ��ȡ������Ϣ
	int		Error(void);

	// Э��ͷ
	struct Header
	{
		int	msg_len;		// ��Ϣ����
	};

	static const int HEADER_LENGTH = sizeof(Header);

	static const int MAX_SERVER_NUM = 32;

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