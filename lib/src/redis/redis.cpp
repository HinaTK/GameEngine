
#include "redis.h"
#include "lib/include/frame/netmanager.h"

Redis::Redis()
: m_net_manager(NULL)
, m_net_handle(0)
{

}

Redis::~Redis()
{

}

bool Redis::Connect(char *ip, unsigned short port, Listener *lister)
{
	m_net_handle = m_net_manager->ConnectServer(ip, port, lister);
	if (m_net_handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	return true;
}

void Redis::Command(const char *command, unsigned int length)
{
	m_net_manager->Send(m_net_handle, command, length);
}
