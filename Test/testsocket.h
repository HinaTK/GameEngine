
#ifndef TEST_SOCKET_H
#define TEST_SOCKET_H

#ifdef WIN32

#include <winsock.h>
#pragma comment(lib,"Wsock32.lib")


namespace TestSocket
{
	class MessageHeader
	{
	public:
		MessageHeader() :msg_type(0){}
		MessageHeader(unsigned short type) :msg_type(type), msg_len(0){}
		unsigned int	msg_type;
		unsigned int	msg_len;		// 消息长度
	};

	void Connect()
	{
		WSADATA Data;

		SOCKADDR_IN destSockAddr;
		unsigned long destAddr;
		int status;

		status = WSAStartup(MAKEWORD(1, 1), &Data);

		destAddr = inet_addr("127.0.0.1");

		memcpy(&destSockAddr.sin_addr, &destAddr, sizeof(destAddr));

		destSockAddr.sin_port = htons(12345);

		destSockAddr.sin_family = AF_INET;

		SOCKET destSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (destSocket == INVALID_SOCKET)
		{
			MessageBox(NULL, L"初始化socket失败", L"消息", MB_OK);
			status = WSACleanup();

			return;
		}
		status = connect(destSocket, (LPSOCKADDR)&destSockAddr, sizeof(destSockAddr));
		if (status == SOCKET_ERROR)
		{
			MessageBox(NULL, L"连接失败", L"消息", MB_OK);
			closesocket(destSocket);
			WSACleanup();

			return;
		}
		struct Msg
		{
			MessageHeader	header;
			char buffer[16];
		};
		Msg msg;
		memcpy(msg.buffer, "123", 3);
		msg.buffer[3] = 0;
		msg.header.msg_len = sizeof(Msg);

		int len = send(destSocket, (const char *)&msg, sizeof(msg), 0);
		if (len <= 0)
		{
			MessageBox(NULL, L"（send）连接丢失", L"消息", MB_OK);
			closesocket(destSocket);
			WSACleanup();
		}
		return;
	}

	void Connect1()
	{
		WSADATA Data;

		SOCKADDR_IN destSockAddr;
		unsigned long destAddr;
		int status;

		status = WSAStartup(MAKEWORD(1, 1), &Data);

		destAddr = inet_addr("127.0.0.1");

		memcpy(&destSockAddr.sin_addr, &destAddr, sizeof(destAddr));

		destSockAddr.sin_port = htons(12345);

		destSockAddr.sin_family = AF_INET;

		SOCKET destSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (destSocket == INVALID_SOCKET)
		{
			MessageBox(NULL, L"初始化socket失败", L"消息", MB_OK);
			status = WSACleanup();

			return;
		}
		status = connect(destSocket, (LPSOCKADDR)&destSockAddr, sizeof(destSockAddr));
		if (status == SOCKET_ERROR)
		{
			MessageBox(NULL, L"连接失败", L"消息", MB_OK);
			closesocket(destSocket);
			WSACleanup();

			return;
		}

		struct Msg
		{
			int len;
			char *buffer;
		};
		int msg_len = 16668;
		Msg msg;
		msg.len = msg_len + 4;
		msg.buffer = new char[msg_len];
		msg.buffer[0] = 1;
		msg.buffer[1] = 2;
		msg.buffer[2] = 3;
		int len = send(destSocket, (const char *)&msg, msg.len, 0);
		delete msg.buffer;
		printf("reallen = %d, len = %d\n", msg.len, len);
		if (len <= 0)
		{
			MessageBox(NULL, L"（send）连接丢失", L"消息", MB_OK);
			closesocket(destSocket);
			WSACleanup();
		}
		return;
	}
}
#endif // WIN32
#endif