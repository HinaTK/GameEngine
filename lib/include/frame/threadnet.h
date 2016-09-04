
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
	
	typedef game::Array<NetHandler*>		NET_HANDLER_ARRAY;
	NET_HANDLER_ARRAY *GetNetHandlerArray(){ return &m_net_handler; }
	NetHandle		AddNetHandler(NetHandler *handler);

	virtual void	SetCanWrite(NetHandler *handler) = 0;
	virtual void	SetCanNotWrite(NetHandler *handler) = 0;

	void			RemoveHandler(NetHandle handle, int err = 0, int reason = 0);
	void			Recv(unsigned short msg_index, NetMsgType msg_type, NetMsg &msg);

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
protected:
	struct RemoveInfo
	{
		NetHandle handle;
		NetCommon::ErrInfo show;
	};
	typedef game::Array<NetHandler*>		NET_HANDLER_ARRAY;
	typedef game::Array<MsgHandler *>		MSG_HANDLER;
	typedef game::Vector<RemoveInfo>		INVALID_HANDLE;
	//typedef MsgMemoryManager<NetMsg>		MSG_MEMORY;

	NET_HANDLER_ARRAY		m_net_handler;
	MsgMemoryManager		m_net_memory;
	MSG_HANDLER				m_msg_handler;
	INVALID_HANDLE			m_invalid_handle;
};

#endif
