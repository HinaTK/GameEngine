
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
		ID_MAIN,
		ID_DB,
		ID_MAX,
		
	};

	void	Register(unsigned char id, BaseThread *bt);
	void	Start();
	void	Update();
	void	Exit();
	void	Wait();
	bool	IsRun(){ return !m_is_exit; }

	void	PushMsg(unsigned char id, ThreadMsg *msg);
private:
	BaseThread	*m_thread[ID_MAX];
	std::thread	*m_forward_thread;
	bool		m_is_exit;
};

#endif