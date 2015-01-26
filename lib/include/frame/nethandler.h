
#ifndef NET_HANDLER_H
#define NET_HANDLER_H

#include "common/systemdef.h"
#include "common/datastructure/msgqueue.h"

class NetManager;
class NetHandler
{
public:
	NetHandler(NetManager *manager, int type)
		: m_handle(0)
		, m_net_id(0)
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

	NetHandle	m_handle;	// �ڲ��������
	NetID		m_net_id;	// socket id
protected:
	NetManager	*m_net_manager;
	int			m_type;
};

#endif