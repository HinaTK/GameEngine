
#include "inaccepter.h"
#include "inlistener.h"
#include "lib/include/frame/netmanager.h"
#include "common/socketdef.h"



INAccepter::INAccepter(SocketThread *t, int size)
: Accepter(t, NetHandler::BASE_ACCEPTER)
, buf_size(size)
{

}


void INAccepter::OnCanRead()
{
	static struct sockaddr_in addr;
	static SOCKET_LEN len = sizeof(struct sockaddr);
	SOCKET new_sock = accept(m_sock, (struct sockaddr*)&addr, &len);
	if (new_sock != INVALID_SOCKET)
	{
		INListener *handler = new INListener(m_thread, buf_size);
		handler->m_msg_index = m_msg_index;
		handler->m_sock = new_sock;
		handler->m_handle = m_thread->AddNetHandler(handler);
		m_thread->PushData(handler, BaseMsg::MSG_ACCEPT, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)) + 1);
	}
}

