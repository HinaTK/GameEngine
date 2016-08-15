

#include "gateaccepter.h"
#include "gatelistener.h"
#include "lib/include/frame/netmanager.h"
#include "common/socketdef.h"



GateAccepter::GateAccepter(SocketThread *t, int size)
: Accepter(t, NetHandler::BASE_ACCEPTER)
, buf_size(size)
{

}


void GateAccepter::OnCanRead()
{
	static struct sockaddr_in addr;
	static SOCKET_LEN len = sizeof(struct sockaddr);
	SOCKET new_sock = accept(m_sock, (struct sockaddr*)&addr, &len);
	if (new_sock != INVALID_SOCKET)
	{
		GateListener *handler = new GateListener(m_thread, buf_size);
		handler->m_msg_index = m_msg_index;
		handler->m_sock = new_sock;
		handler->m_handle = m_thread->AddNetHandler(handler);
		
		m_thread->PushNetMsg(handler, BaseMsg::MSG_ACCEPT, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)));
	}
}
