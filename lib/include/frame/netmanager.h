
#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include <thread>
#include "nethandler.h"
#include "message.h"
#include "socketthread.h"
#include "common/socketdef.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/mutex.h"

typedef MsgQueue<GameMsg *> NetMessage;

class Accepter;
class Listener;

class NetManager
{
public:
	virtual ~NetManager();
	NetManager();

	struct MsgHandler
	{
		BaseMsg *msg[BaseMsg::MSG_MAX];
	};

	void			SetThread(SocketThread *st){ m_thread = st; };
	void			SetCanWrite(NetHandler *handler){ m_thread->SetCanWrite(handler); };
	void			SetCanNotWrite(NetHandler *handler){ m_thread->SetCanNotWrite(handler); };
	NetHandle		AddNetHandler(NetHandler *handler){ return m_thread->AddNetHandler(handler); };
	void			RemoveHandler(NetHandle handle, int reason){ m_thread->RemoveHandler(handle, reason); };

	bool			InitServer(char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back);
	NetHandle		SyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back);
	void			AsyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back, int flag = 0);
	void			Listen();
	void			Send(NetHandle handle, unsigned int length, const char *buf);
	bool			Update();

	
	void			AddReplaceHandler(NetHandler *handler);

	void			PushMsg(NetHandler *handler, unsigned short msg_type, const char *data, unsigned int len);

protected:
	unsigned int	AddMsgHandler(MsgCallBack *call_back);
public:


protected:
	typedef game::Vector<NetHandler*>	REPLACE_HANDLER;
	typedef game::Array<MsgHandler *>	MSG_HANDLER;

	NetMessage			m_queue;
	REPLACE_HANDLER		m_replace_handler;
	std::mutex			m_net_mutex;
	SocketThread		*m_thread;
	MSG_HANDLER			m_msg_handler;
};

#endif
