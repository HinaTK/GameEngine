
#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include <thread>
#include "message.h"
#include "common/socketdef.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/mutex.h"

/*
	NetManager 由外部线程调用，线程安全，不影响内部
*/

class MsgHandler
{
public:
	MsgHandler(MsgCallBack *call_back);
	~MsgHandler();

	inline void Recv(GameMsgType msg_type, GameMsg &msg)
	{
		m_bm[msg_type]->Recv(&msg);
	}
private:
	BaseMsg *m_bm[BaseMsg::MSG_MAX];
};

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

    void			SetThread(SocketThread *st){ m_thread = st; }
	SocketThread	*GetThread(){ return m_thread; }

	bool			InitServer(char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back);
	NetHandle		SyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back);
	void			AsyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back, int flag = 0);
	void			Send(NetHandle handle, unsigned int length, const char *buf);
	bool			Update();

	
	void			AddReplaceHandler(NetHandler *handler);
	void			RemoveHandler(NetHandle handle);

protected:
	unsigned int	AddMsgHandler(MsgCallBack *call_back);
public:


protected:
	typedef game::Vector<NetHandler*>	REPLACE_HANDLER;
	typedef game::Array<MsgHandler *>	MSG_HANDLER;

	REPLACE_HANDLER		m_replace_handler;
	SocketThread		*m_thread;
	MSG_HANDLER			m_msg_handler;
};

#endif
