
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
		T_DB,
		T_MAX,
	};

	void	Start();

private:
	BaseThread	**m_thread;
};

#endif