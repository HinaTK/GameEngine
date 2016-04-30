
#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <thread>
#include "threadmanager.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/frame/message.h"
#include "lib/include/timemanager/gametime.h"

/*
	目的：以多线程并行代替多进程并行
*/

class BaseThread
{
public:
	/* 
		arg 必须是指针，不用强制转换引用，原因如下：
		* 函数结束会被析构;
		继承者自己在 init 中决定是否释放 arg
	*/
	BaseThread(ThreadManager *manager, void *arg, char exit = ThreadManager::EXIT_NORMAL);
	virtual ~BaseThread();

	void	SetID(int id){ m_id = id; }
	void	Start();
	void	Loop(bool sleep = true);

	void	PushMsg(ThreadMsg *msg);
	void	Exit();
	void	Wait();

private:
	// 不允许复制
	BaseThread(const BaseThread&);
	void operator=(const BaseThread&);
protected:
	virtual void	Init(void *arg) = 0;
	virtual bool	Run() = 0;
	virtual void	RecvData(short type, int sid, int len, const char *data) = 0;
protected:
	int				m_id;
	ThreadManager	*m_manager;
	std::thread		*m_thread;
	bool			m_is_start;
	bool			m_is_exit;

	MsgQueue<ThreadMsg *> m_recv_queue;

private:
	void			*m_arg;
};

#endif 

