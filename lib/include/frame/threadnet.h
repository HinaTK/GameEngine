
#ifndef THREAD_NET_H
#define THREAD_NET_H

#include "netmanager.h"
#include "common/datastructure/gamearray.h"
#include "lib/include/thread/basethread.h"


class NetHandler;
class ThreadNet : public BaseThread
{
public:
	ThreadNet(ThreadManager *manager, NetManager *net_manager);
	virtual ~ThreadNet();

	NetHandle		AddNetHandler(NetHandler *handler);
	void			RemoveHandler(NetHandle handle, int err, int reason = 0);

	virtual void	SetCanWrite(NetHandler *handler) = 0;
	virtual void	SetCanNotWrite(NetHandler *handler) = 0;

	virtual void	ClearHandler() = 0;

	GameMsg *		CreateGameMsg(unsigned int msg_index, unsigned short msg_type, NetHandle handle, unsigned int length)
	{ 
		return m_net_manager->CreateMsg(msg_index, msg_type,handle, length);
	};
	void			PushData(NetHandler *handler, unsigned short msg_type, const char *data, unsigned int len){m_net_manager->PushMsg(handler, msg_type, data, len); }
	void			PushGameMsg(GameMsg *msg){ m_net_manager->PushMsg(msg); };

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

	NetManager		*m_net_manager;

	typedef game::Array<NetHandler*>	NET_HANDLER_ARRAY;
	typedef game::Vector<RemoveInfo>	INVALID_HANDLE;

	NET_HANDLER_ARRAY		m_net_handler;
	INVALID_HANDLE			m_invalid_handle;
};

#endif
