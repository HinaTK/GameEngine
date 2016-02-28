﻿
#ifndef NET_HANDLER_H
#define NET_HANDLER_H

//#include "netmanager.h"
#include "msgproxy.h"
#include "msgcallback.h"
#include "common/socketdef.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/memorypool.h"

class NetManager;
class NetHandler
{
public:
	NetHandler(NetManager *manager, int type);
	virtual ~NetHandler();

	virtual void	OnCanRead() = 0;

	virtual void	OnCanWrite(){}

	int	Type(){ return m_type; }

	NetManager *GetNetManager(){ return m_net_manager; }

	enum 
	{
		BASE_ACCEPTER,
		INNER_ACCEPTER,
		WEB_ACCEPTER,
		HANDSHAKER,
		LISTENER,
	};

	// disconnect reason
	enum
	{
		DR_RECV_BUF = 1,
		DR_SEND_BUF,
		DR_HEADER_TOO_SMALL,
		DR_HEADER_TOO_BIG,
		DR_HANDSHAKE_RECV,
		DR_HANDSHAKE_SEND,
	};

	NetHandle		m_handle;		// 内部操作句柄
	SOCKET			m_sock;			// socket id
	unsigned int	m_msg_index;	// 网络数据导向索引
protected:
	NetManager	*m_net_manager;
	int			m_type;
	MsgCallBack *m_call_back;
};

#endif
