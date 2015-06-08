
#ifndef NET_HANDLER_H
#define NET_HANDLER_H

#include "common/socketdef.h"
#include "common/datastructure/msgqueue.h"

class NetManager;
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

	enum 
	{
		ACCEPTER,
		WEB_ACCEPTER,
		HANDSHAKER,
		LISTENER,
	};

	NetHandle	m_handle;	// ÄÚ²¿²Ù×÷¾ä±ú
	SOCKET		m_sock;	// socket id
protected:
	NetManager	*m_net_manager;
	int			m_type;
};

#endif