
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
	void	Exit();
	void	Wait();
	bool	IsRun(){ return !m_is_exit; }

	void	SendMsg(unsigned char id, ThreadMsg *msg);
private:
	BaseThread	*m_thread[ID_MAX];
	bool		m_is_exit;
};

#endif