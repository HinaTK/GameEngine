
#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include <map>
#include "nethandler.h"
#include "message.h"
#include "msgcallback.h"
#include "msgproxy.h"
#include "common/socketdef.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/msgqueue.h"

typedef MsgQueue<GameMsg *> NetMessage;

class Accepter;
class Listener;
class NetManager
{
public:
	~NetManager();
	NetManager();
	
	bool			InitServer(char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back);
	NetHandle		ConnectServer(const char *ip, unsigned short port, Listener *lister, MsgCallBack *call_back);

	void			Listen();
	void			Send(NetHandle handle, const char *buf, unsigned int length);

	void			Update();

	void			InitNetHandler(NetHandler *handler);
	NetHandle		PushNetHandler(NetHandler *handler);
	NetHandle		AddNetHandler(NetHandler *handler);			
	void			RemoveHandler(NetHandle handle);
	void			AddReplaceHandler(NetHandler *handler);

	void			ReplaceHandler();		// 将该句柄的控制者替换（用于将握手者-->监听者）
	void			ClearHandler();
	
	void			PushMsg(NetHandler *handler, unsigned short msg_type, const char *data, unsigned int len);

	NetMessage		*GetMsgQueue(){ return &m_queue; }
	void			Exit(){ m_is_run = false; }

protected:
	unsigned int	AddMsgHandler(MsgCallBack *call_back);
public:
	typedef game::Array<NetHandler*>	NET_HANDLER_ARRAY;
	NET_HANDLER_ARRAY		m_net_handler;

	struct MsgHandler
	{
		BaseMsg *msg[BaseMsg::MSG_MAX];
	};
protected:
	typedef game::Vector<NetHandle>		INVALID_HANDLE;
	typedef game::Vector<NetHandler*>	REPLACE_HANDLER;
	typedef game::Array<MsgHandler *>	MSG_HANDLER;

	NetMessage			m_queue;
	INVALID_HANDLE		m_invalid_handle;
	REPLACE_HANDLER		m_replace_handler;
	bool				m_is_run;
	MSG_HANDLER			m_msg_handler;

#ifdef WIN32
public:

	SOCKET			GetSocketInfo(fd_set &read_set, fd_set &write_set);
	fd_set			*GetWriteSet(){ return &m_write_set; }
	fd_set			*GetReadSet(){ return &m_read_set; }

protected:
	SOCKET			m_max_fd;
	fd_set			m_read_set;
	fd_set			m_write_set;
#endif

#ifdef __unix
public:
	SOCKET			GetEpollFD(){return m_epoll_fd;}
protected:
	SOCKET			m_epoll_fd;
#endif

};

#endif
