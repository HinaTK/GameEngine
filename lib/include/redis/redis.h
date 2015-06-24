
#ifndef REDIS_H
#define REDIS_H

#include "common/socketdef.h"
#include "lib/include/frame/listener.h"

class NetManager;
class MsgCallBack;
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

class RedisListener : public Listener
{
public:
	RedisListener(NetManager *manager, MsgCallBack *call_back);
	~RedisListener(){}
	bool AnalyzeBuf();
};
#endif