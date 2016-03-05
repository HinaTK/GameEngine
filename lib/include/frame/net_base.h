
#ifndef NET_BASE_H
#define NET_BASE_H

#include <thread>
#include "nethandler.h"
#include "message.h"
#include "msgcallback.h"
#include "msgproxy.h"
#include "common/socketdef.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/mutex.h"

typedef MsgQueue<GameMsg *> NetMessage;

class Accepter;
class Listener;

class NetBase
{
public:
	virtual ~NetBase();
	NetBase();
	virtual void	Loop() = 0;
    virtual void	SetCanWrite(NetHandler *handler) = 0;
    virtual void	SetCanNotWrite(NetHandler *handler) = 0;

	bool			InitServer(char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back);
	NetHandle		ConnectServer(const char *ip, unsigned short port, Listener *lister, MsgCallBack *call_back);
	void			Listen();
	bool			Send(NetHandle handle, const char *buf, unsigned int length);
	void			Update();

	NetHandle		AddNetHandler(NetHandler *handler);
	void			RemoveHandler(NetHandle handle, int reason);
	void			AddReplaceHandler(NetHandler *handler);	
	
	void			PushMsg(NetHandler *handler, unsigned short msg_type, const char *data, unsigned int len);
	NetMessage		*GetMsgQueue(){ return &m_queue; }
	void			Exit();
	void			Wait();
	bool			IsRun(){ return m_is_run; }

protected:
	
	virtual void	InitNetHandler(NetHandler *handler) = 0;
	virtual void	ReplaceHandler() = 0;		// 将该句柄的控制者替换（用于将握手者-->监听者）
	virtual void	ClearHandler() = 0;

	unsigned int	AddMsgHandler(MsgCallBack *call_back);
public:
	typedef game::Array<NetHandler*>	NET_HANDLER_ARRAY;
	NET_HANDLER_ARRAY		m_net_handler;

	struct MsgHandler
	{
		BaseMsg *msg[BaseMsg::MSG_MAX];
	};

	struct RemoveInfo
	{
		NetHandle handle;
		int reason;
	};
protected:
	typedef game::Vector<RemoveInfo>	INVALID_HANDLE;
	typedef game::Vector<NetHandler*>	REPLACE_HANDLER;
	typedef game::Array<MsgHandler *>	MSG_HANDLER;

	NetMessage			m_queue;
	INVALID_HANDLE		m_invalid_handle;
	REPLACE_HANDLER		m_replace_handler;
	bool				m_is_run;
	MSG_HANDLER			m_msg_handler;
	std::mutex			m_net_mutex;
	std::thread			*m_listen_thread;
};

#endif
