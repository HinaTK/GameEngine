
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "basethread.h"
#include "common/datastructure/gamearray.h"
#include <vector>

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	// 线程退出先后顺序
	enum
	{
		EXIT_NORMAL = 0,
		EXIT_DELAY,
		EXIT_FINALLY,
		EXIT_MAX
	};

	enum
	{
		CMD_NOT = 0,	// 
		CMD_EXIT
	};

	int				Register(BaseThread *bt, void *arg = NULL, unsigned int exit = EXIT_NORMAL);
	void			Start();
	void			Exit();
	void			Wait();

	void			SendMsg(unsigned char sid, unsigned char did, int len, const char *data);
	void			CMD(unsigned char type, int sid, int len, const char *data, int did = -1);

private:
	game::Array<BaseThread *>	m_thread;
	std::vector<int>	m_exit[EXIT_MAX];
};

#endif