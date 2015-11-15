
#include <stdio.h>
#include "accepter.h"
#include "baselistener.h"
#include "netmanager.h"
#include "common/socketdef.h"


void Accepter::OnCanRead()
{
	static struct sockaddr_in addr;
	static SOCKET_LEN len = sizeof(struct sockaddr);
	SOCKET new_sock = accept(m_sock, (struct sockaddr*)&addr, &len);
	if (new_sock != INVALID_SOCKET)
	{
		printf("connect server ip = %s\n", inet_ntoa(addr.sin_addr));

		BaseListener *handler = new BaseListener(m_net_manager, m_call_back);
		handler->m_sock = new_sock;
		handler->m_handle = m_net_manager->AddNetHandler(handler);
		m_net_manager->PushMsg(this, NULL, 0);
	}
}