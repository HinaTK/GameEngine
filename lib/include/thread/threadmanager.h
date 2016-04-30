
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "threadsysid.h"
#include "common/datastructure/gamearray.h"
#include <vector>

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
	void			Start();
	void			Exit();
	void			Wait();

	void			SendMsg(short type, unsigned char did, int len, const char *data, int sid = -1);
	void			CMD(short type, int sid, int len, const char *data, int did = -1);

private:
	game::Array<BaseThread *>	m_thread;
	std::vector<BaseThread *>	*m_write_thread;	// 临时保存线程，方便在启动（Start）后，后来加入线程能启动
	std::vector<BaseThread *>	*m_read_thread;
	std::vector<int>	m_exit[EXIT_MAX];
};

#endif