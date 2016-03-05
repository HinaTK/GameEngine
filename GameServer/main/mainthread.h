
#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H

#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"

class ThreadManager;
class MainThread : public BaseThread
{
public:
	virtual ~MainThread(){}
	MainThread(ThreadManager *manager);

protected:
	void	Init();
	void	Run();
	void	RecvMsg(unsigned char sid, int len, const char *data);
private:
	NetManager	m_net_manager;
};

#endif