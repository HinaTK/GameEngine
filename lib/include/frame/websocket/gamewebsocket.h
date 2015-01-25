
#ifndef GAME_WEBSOCKET_H
#define GAME_WEBSOCKET_H


#ifdef WIN32
#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif
#define FD_SETSIZE		4096
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <Windows.h>
#endif

#include <string>
#include "common/datastructure/webmsgqueue.h"
#include "common/datastructure/gamevector.h"
#include "frame/netmanager.h"

typedef unsigned short  UInt16;


class GameWebSocket
{
public:
	GameWebSocket();
	~GameWebSocket();


	bool		Init(char * ip, UInt16 port, int backlog);

	void		Accept(NetID net_id);

	bool		Listen();

	bool		OnSend(NetID net_id, const char *msg, unsigned int length);

protected:
	bool		WaitHand(NetID fd);			// 等待握手
	bool		HandShake(NetID fd);		// 进行握手
	void		DisConnect(NetID net_id);
	bool		RecvBuf(NetID net_id);
	bool		AnalyzeBuf(NetUser *user);
private:
	NetManager			m_net_manager;
	NetID				m_listener;
	char				m_recv_buf[MAX_EXTERNAL_BUF];
	char				m_des_buf[MAX_EXTERNAL_BUF];
	WebMsgQueue			m_send_queue;
	WebMsgQueue			m_recv_queue;

	std::string			m_handshake;
	std::string			m_header;
	std::string			m_key;
	std::string			m_magic_key;

#ifdef WIN32
	fd_set				m_read_fd;
#endif
};


#endif