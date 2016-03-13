
#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H

#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"
#include "lua/interface.h"

class ThreadManager;
class MainThread : public BaseThread
{
public:
	virtual ~MainThread(){}
	MainThread(ThreadManager *manager);

protected:
	void	Init();
	bool	Run();
	void	RecvMsg(ThreadMsg *msg);
private:
	NetManager	m_net_manager;
	Interface	m_lua_interface;
};

#endif