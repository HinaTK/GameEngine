

#include "baseaccepter.h"
#include "baselistener.h"
#include "netmanager.h"
#include "common/socketdef.h"



BaseAccepter::BaseAccepter(NetManager *manager, int size)
: Accepter(manager, NetHandler::BASE_ACCEPTER)
, buf_size(size)
{

}


void BaseAccepter::OnCanRead()
{
	static struct sockaddr_in addr;
	static SOCKET_LEN len = sizeof(struct sockaddr);
	SOCKET new_sock = accept(m_sock, (struct sockaddr*)&addr, &len);
	if (new_sock != INVALID_SOCKET)
	{
		BaseListener *handler = new BaseListener(m_net_manager, buf_size);
		handler->m_msg_index = m_msg_index;
		handler->m_sock = new_sock;
		handler->m_handle = m_net_manager->AddNetHandler(handler);
		m_net_manager->PushMsg(handler, BaseMsg::MSG_ACCEPT, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)) + 1);
	}
}

