
#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H

#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"

class ThreadManager;
class MainThread : public BaseThread
{
public:
	~MainThread(){}
	MainThread(ThreadManager *manager);

	void	Run();
protected:
	void	Init();
private:
	NetManager	m_net_manager;
};

#endif