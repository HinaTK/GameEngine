
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
	NetThread(ThreadManager *manager, SocketThread *st);

protected:
	bool	Init();
	bool	Ready();
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	NetManager		m_net_manager;
	NetHandle		m_cneter_handle;
	WorldManager	m_world_manager;
};

#endif