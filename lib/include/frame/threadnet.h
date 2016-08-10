
#ifndef THREAD_NET_H
#define THREAD_NET_H

#include "netmanager.h"
#include "common/datastructure/gamearray.h"
#include "lib/include/thread/basethread.h"


class NetHandler;
class ThreadNet : public BaseThread
{
public:
	ThreadNet(ThreadManager *manager);
	virtual ~ThreadNet();

	typedef MsgQueue<GameMsg> 			NetMessage;
	
	NetHandle		AddNetHandler(NetHandler *handler);
	void			RemoveHandler(NetHandle handle, int err, int reason = 0);

	virtual void	SetCanWrite(NetHandler *handler) = 0;
	virtual void	SetCanNotWrite(NetHandler *handler) = 0;

	virtual void	ClearHandler() = 0;

	char *			CreateData(unsigned int length){ return m_msg_manager.Alloc(length); };
	void			PushGameMsg(GameMsg &msg);
	void			PushGameMsg(NetHandler *handler, GameMsgType msg_type, const char *data, unsigned int len);

	NetMessage 		*GetQueue(){ return &m_queue; }
	void			Release(GameMsg &msg){ m_msg_manager.Free(msg); }
protected:
	virtual void	InitNetHandler(NetHandler *handler) = 0;
	void			RecvData(short type, ThreadID sid, int len, const char *data);
	void			AddHandler(const char *data);
	void			SendMsg(NetHandle handle, int length, const char *data);
	
protected:
	struct RemoveInfo
	{
		NetHandle handle;
		NetCommon::ErrInfo show;
	};

	typedef game::Array<NetHandler*>	NET_HANDLER_ARRAY;
	typedef game::Vector<RemoveInfo>	INVALID_HANDLE;
	

	NET_HANDLER_ARRAY		m_net_handler;
	INVALID_HANDLE			m_invalid_handle;
	NetMessage				m_queue;
	GameMsgManager			m_msg_manager;
};

#endif
