
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "basethread.h"

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	enum 
	{
		T_MAIN,
		T_DB,
		T_MAX,
		T_CHAT,
		T_LOGIN,
		
	};

	void	Start();
	void	Update();
	void	Exit();
	void	Wait();

	void	PushMsg(unsigned char type, ThreadMsg *msg);
	void	PushGlobal(unsigned char type, ThreadMsg *msg);
private:
	BaseThread	**m_thread;
	MsgQueue<GlobalMsg *> m_global_queue;
};

#endif