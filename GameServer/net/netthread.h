
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"
#include "world/worldmanager.h"

class ThreadManager;
class NetThread : public BaseThread
{
public:
	virtual ~NetThread(){}
	NetThread(ThreadManager *manager);

protected:
	void	Init(void *arg);
	bool	Run();
	void	RecvData(short type, int sid, int len, const char *data);
private:
	NetManager		m_net_manager;
	WorldManager	m_world_manager;
};

#endif