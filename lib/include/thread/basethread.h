
#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <thread>
#include "common/datastructure/msgqueue.h"
#include "lib/include/frame/message.h"
#include "lib/include/timemanager/gametime.h"

/*
	目的：以多线程并行代替多进程并行
*/

class ThreadManager;
class BaseThread
{
public:
	BaseThread(ThreadManager *manager);
	virtual ~BaseThread();

	void	Start();
	virtual void Update() = 0;

	void			PushMsg(ThreadMsg *msg);
	bool			PopMsg(GlobalMsg *msg);

	void			Exit(){ m_is_exit = true; }
	void			Wait();

protected:
	ThreadManager	*m_manager;
	std::thread		*m_thread;
	bool			m_is_exit;

	MsgQueue<ThreadMsg *> m_recv_queue;
	MsgQueue<GlobalMsg *> m_send_queue;
};

#endif 

