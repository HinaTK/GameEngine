
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

		BaseListener *handler = new BaseListener(m_net_manager);
		handler->m_msg_index = m_msg_index;
		handler->m_sock = new_sock;
		handler->m_handle = m_net_manager->AddNetHandler(handler);
		m_net_manager->PushMsg(this, BaseMsg::MSG_ACCEPT, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)) + 1);
	}
}