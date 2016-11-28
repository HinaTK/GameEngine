
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <vector>
#include "threadsysid.h"
#include "common/serverdef.h"
#include "common/datastructure/gamearray.h"

#define POINT_2_CLASS(Point, Class) *(Class *)&Point

class ThreadMsg;
class BaseThread;
class ThreadClass;
class ThreadRPC;
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
	void			Start();
	void			Exit();
	void			Wait();

	bool			SendMsg(ThreadID did, ThreadMsg &msg);
	void			SendMsg(ThreadID did, TPT type, int len, const char *data, ThreadID sid = INVALID_THREAD_ID);
	void 			SendMsg(ThreadID did, ThreadClass * tc);
	void 			SendMsg(ThreadID did, TPT type, char *obj, ThreadID sid = INVALID_THREAD_ID);
	void 			SendMsg(ThreadID did, TPT type, int data, ThreadID sid = INVALID_THREAD_ID);
	void 			SendMsg(ThreadID did, TPT type, unsigned int data, ThreadID sid = INVALID_THREAD_ID);
	void 			SendMsg(ThreadID did, TPT type, long long data, ThreadID sid = INVALID_THREAD_ID);
	void 			SendMsg(ThreadID did, TPT type, unsigned long long data, ThreadID sid = INVALID_THREAD_ID);
	void			RPC(ThreadID did, ThreadRPC *rpc);
	
	char *			CreateData(ThreadID did, int len);
	void			CMD(TPT type, ThreadID sid, int len, const char *data, ThreadID did = INVALID_THREAD_ID);

	game::Array<BaseThread *> *GetThreads(){ return &m_thread; }

private:
	game::Array<BaseThread *>	m_thread;
	std::vector<int>			m_exit[EXIT_MAX];
};

#endif