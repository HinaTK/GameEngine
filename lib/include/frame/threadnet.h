
#ifndef THREAD_NET_H
#define THREAD_NET_H

#include "common/datastructure/gamearray.h"
#include "lib/include/thread/basethread.h"

class MsgHandler
{
public:
	MsgHandler(MsgCallBack *call_back);
	~MsgHandler();

	inline void Recv(NetMsgType msg_type, NetMsg &msg)
	{
		m_bm[msg_type]->Recv(&msg);
	}
private:
	BaseMsg *m_bm[BaseMsg::MSG_MAX];
};

class NetHandler;
class Accepter;
class Listener;
class ThreadNet : public BaseThread
{
public:
	ThreadNet(ThreadManager *manager);
	virtual ~ThreadNet();
	
	NetHandle		AddNetHandler(NetHandler *handler);
	void			RemoveHandler(NetHandle handle, int err, int reason = 0);

	virtual void	SetCanWrite(NetHandler *handler) = 0;
	virtual void	SetCanNotWrite(NetHandler *handler) = 0;

	virtual void	ClearHandler() = 0;
	void			Recv(unsigned int msg_index, NetMsgType msg_type, NetMsg &msg);

	bool			InitServer(const char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back);
	NetHandle		SyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back);
	void			AsyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back, int flag = 0);

	char *			CreateData(unsigned int length){ return m_msg_memory.Alloc(length); };
	
	void			Release(NetMsg &msg){ m_msg_memory.Free(msg); }
protected:
	virtual void	InitNetHandler(NetHandler *handler) = 0;
	virtual bool	DoSomething(){ return false; }
	void			RecvData(short type, ThreadID sid, int len, const char *data);
	void			AddHandler(const char *data);
	void			Send(NetHandle handle, int length, const char *data);
	unsigned int	AddMsgHandler(MsgCallBack *call_back);
protected:
	struct RemoveInfo
	{
		NetHandle handle;
		NetCommon::ErrInfo show;
	};

	typedef game::Array<NetHandler*>		NET_HANDLER_ARRAY;
	typedef game::Vector<RemoveInfo>		INVALID_HANDLE;
	typedef game::Array<MsgHandler *>		MSG_HANDLER;
	//typedef MsgMemoryManager<NetMsg>		MSG_MEMORY;

	NET_HANDLER_ARRAY		m_net_handler;
	INVALID_HANDLE			m_invalid_handle;
	MsgMemoryManager		m_net_memory;
	MSG_HANDLER				m_msg_handler;
};

#endif
