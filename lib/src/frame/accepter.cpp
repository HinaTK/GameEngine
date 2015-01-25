
#include "accepter.h"
#include "listener.h"
#include "netmanager.h"
#include "common/socketdef.h"

REGISTER_MEMORYPOOL(memorypool, Accepter, 64);

void Accepter::OnCanRead()
{
	static struct sockaddr_in addr;
	static SOCKET_LEN len = sizeof(struct sockaddr);
	NetID new_net_id = accept(m_net_id, (struct sockaddr*)&addr, &len);
	if (new_net_id != INVALID_SOCKET)
	{
		Listener *handler = new Listener(m_net_manager, NetHandler::LISTENER);
		handler->m_net_id = new_net_id;
		m_net_manager->AddNetHandler(handler);
	}
}

