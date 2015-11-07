
#ifndef NET_HANDLER_H
#define NET_HANDLER_H

#include "common/socketdef.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/memorypool.h"

class NetManager;
class MsgCallBack;
class NetHandler
{
public:
	NetHandler(NetManager *manager, int type)
		: m_handle(0)
		, m_sock(0)
		, m_net_manager(manager)
		, m_type(type)
	{
	}
	virtual ~NetHandler(){};

	virtual void	OnCanRead() = 0;

	virtual void	OnCanWrite(){}

	int	Type(){ return m_type; }

	NetManager *GetNetManager(){ return m_net_manager; }

	enum 
	{
		ACCEPTER,
		WEB_ACCEPTER,
		HANDSHAKER,
		LISTENER,
	};

	NetHandle	m_handle;	// �ڲ��������
	SOCKET		m_sock;	// socket id
protected:
	NetManager	*m_net_manager;
	int			m_type;
};

#endif