
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "lib/include/thread/basethread.h"
#include "lib/include/frame/socketthread.h"

class ThreadManager;
class NetThread : public SocketThread
{
public:
	virtual ~NetThread(){}
	NetThread(ThreadManager *manager);

protected:
	bool	Init();
	void	Ready();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	NetHandle		m_cneter_handle;
};

#endif