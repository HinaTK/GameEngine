
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "gamethread.h"

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	enum 
	{
		T_DB,
		T_MAX,
	};

	void	Start();

private:
	BaseThread	*m_thread;
};

#endif