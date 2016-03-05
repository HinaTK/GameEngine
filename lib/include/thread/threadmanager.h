﻿
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "basethread.h"
#include <vector>

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	enum 
	{
		ID_FRAME,
		ID_MAIN,
		ID_DB,
		ID_LOGIN,
		ID_CHAT,
		ID_GATE,
		ID_GATE2,
		ID_LOG,
		ID_MAX,	
	};

	enum
	{
		EXIT_NORMAL = 0,
		EXIT_DELAY,
		EXIT_FINALLY,
		EXIT_MAX
	};

	void	Register(unsigned char id, BaseThread *bt, unsigned int exit = EXIT_NORMAL);
	void	Start();
	void	Exit();
	void	Wait();

	void	SendMsg(unsigned char id, ThreadMsg *msg);
private:
	BaseThread	*m_thread[ID_MAX];
	std::vector<unsigned char>	m_exit[EXIT_MAX];
};

#endif