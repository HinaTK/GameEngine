
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <vector>
#include "threadsysid.h"
#include "common/serverdef.h"
#include "common/datastructure/gamearray.h"

class ThreadMsg;
class BaseThread;
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

	int				Register(BaseThread *bt, char exit = EXIT_NORMAL);
	bool			Init();
	bool			Ready();
	void			Start();
	void			Exit();
	void			Wait();

	void			SendMsg(ThreadID did, short type, int len, const char *data, ThreadID sid = INVALID_THREAD_ID);
	void			SendMsg(ThreadID did, ThreadMsg &msg);
	void			CMD(short type, ThreadID sid, int len, const char *data, ThreadID did = INVALID_THREAD_ID);

	game::Array<BaseThread *> *GetThreads(){ return &m_thread; }

private:
	game::Array<BaseThread *>	m_thread;
	std::vector<int>			m_exit[EXIT_MAX];
};

#endif