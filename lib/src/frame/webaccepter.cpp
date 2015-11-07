
#include "webaccepter.h"
#include "handshaker.h"
#include "netmanager.h"
#include "common/socketdef.h"

REGISTER_MEMORYPOOL(memorypool, WebAccepter, 8);

void WebAccepter::OnCanRead()
{
	// 将握手者handshaker加入监听
	static struct sockaddr_in addr;
	static SOCKET_LEN len = sizeof(struct sockaddr);
	SOCKET new_net_id = accept(m_sock, (struct sockaddr*)&addr, &len);
	if (new_net_id != INVALID_SOCKET)
	{
		HandShaker *handler = new HandShaker(m_net_manager, call_back);
		handler->m_sock = new_net_id;
		m_net_manager->AddNetHandler(handler);
	}
}
