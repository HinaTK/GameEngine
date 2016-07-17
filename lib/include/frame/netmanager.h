
#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include <thread>
//#include "nethandler.h"
#include "message.h"
#include "common/socketdef.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/mutex.h"

/*
	NetManager 由外部线程调用，线程安全，不影响内部
*/

class NetHandler;
class Accepter;
class Listener;
class SocketThread;
class ThreadManager;
class NetManager
{
public:
	virtual ~NetManager();
	NetManager(ThreadManager *tm);

	struct MsgHandler
	{
		BaseMsg *msg[BaseMsg::MSG_MAX];
	};

    void			SetThread(SocketThread *st){ m_thread = st; }
	SocketThread	*GetThread(){ return m_thread; }

	bool			InitServer(char *ip, unsigned short port, int backlog, MsgCallBack *call_back);
	bool			InitServer(char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back);
	NetHandle		SyncConnect(const char *ip, unsigned short port, MsgCallBack *call_back);
	NetHandle		SyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back);
	void			AsyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back, int flag = 0);
	void			Listen();
	void			Send(NetHandle handle, unsigned int length, const char *buf);
	bool			Update();

	
	void			AddReplaceHandler(NetHandler *handler);
	void			RemoveHandler(NetHandle handle);

	void			PushMsg(NetHandler *handler, unsigned short msg_type, const char *data, unsigned int len);
	void			PushMsg(GameMsg *msg){ m_queue.Push(msg); }
	GameMsg	*		CreateMsg(unsigned int msg_index, unsigned short msg_type, NetHandle handle, unsigned int len);

protected:
	unsigned int	AddMsgHandler(MsgCallBack *call_back);
public:


protected:
	typedef MsgQueue<GameMsg *> NetMessage;
	typedef game::Vector<NetHandler*>	REPLACE_HANDLER;
	typedef game::Array<MsgHandler *>	MSG_HANDLER;

	NetMessage			m_queue;
	REPLACE_HANDLER		m_replace_handler;
	std::mutex			m_net_mutex;
	SocketThread		*m_thread;
	MSG_HANDLER			m_msg_handler;
	GameMsgManager		m_msg_manager;
};

#endif
