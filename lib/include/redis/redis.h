
#ifndef REDIS_H
#define REDIS_H

#include "common/socketdef.h"

class Listener;
class NetManager;
class Redis
{
public:
	Redis();
	~Redis();

	bool	Connect(char *ip, unsigned short port, Listener *lister);

	void	Command(const char *command, unsigned int length);
private:
	NetManager	*m_net_manager;
	NetHandle	m_net_handle;
};

#endif