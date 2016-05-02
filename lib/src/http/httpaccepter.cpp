
#include "httpaccepter.h"
#include "httplistener.h"

HttpAccepter::HttpAccepter(SocketThread *t, int size /*= 0*/)
: Accepter(t, NetHandler::HTTP_ACCEPTER)
{

}

HttpAccepter::~HttpAccepter()
{

}

void HttpAccepter::OnCanRead()
{
	static struct sockaddr_in addr;
	static SOCKET_LEN len = sizeof(struct sockaddr);
	SOCKET new_sock = accept(m_sock, (struct sockaddr*)&addr, &len);
	if (new_sock != INVALID_SOCKET)
	{
		HttpListener *handler = new HttpListener(m_thread, buf_size);
		handler->m_msg_index = m_msg_index;
		handler->m_sock = new_sock;
		handler->m_handle = m_thread->AddNetHandler(handler);
		m_thread->PushData(handler, BaseMsg::MSG_ACCEPT, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)) + 1);
	}
}

