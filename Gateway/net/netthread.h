
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"

class ThreadManager;
class NetThread : public BaseThread
{
public:
	virtual ~NetThread(){}
	NetThread(ThreadManager *manager);

protected:
	void	Init();
	bool	Run();
	void	RecvMsg(unsigned char sid, int len, const char *data);
private:
	NetManager	m_net_manager;
};

#endif