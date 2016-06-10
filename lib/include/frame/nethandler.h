
#ifndef NET_HANDLER_H
#define NET_HANDLER_H

#include "socketthread.h"
#include "message.h"
#include "common/socketdef.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/memorypool.h"

class SocketThread;
class NetHandler
{
public:
	NetHandler(SocketThread *t, int type)
		: m_handle(0)
		, m_sock(0)
		, m_thread(t)
		, m_type(type)
		, m_err(0){}
	virtual ~NetHandler(){};

	virtual void	OnCanRead() = 0;

	virtual void	OnCanWrite(){}

	int	Type(){ return m_type; }

	int error(){ return m_err; }

	SocketThread *GetThread(){ return m_thread; }
	enum 
	{
		BASE_ACCEPTER,
		INNER_ACCEPTER,
		WEB_ACCEPTER,
		HTTP_ACCEPTER,
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
		DR_MSG_TOO_LONG,
		DR_RECV_FAIL
	};

	NetHandle		m_handle;		// 内部操作句柄
	SOCKET			m_sock;			// socket id
	unsigned int	m_msg_index;	// 网络数据导向索引
protected:
	SocketThread	*m_thread;
	int				m_type;
	MsgCallBack		*m_call_back;
	int				m_err;
};

#endif
