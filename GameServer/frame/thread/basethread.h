
#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <thread>
#include "define.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/frame/message.h"
/*
	目的：以多线程并行代替多进程并行
*/

class BaseThread
{
public:
	BaseThread();
	virtual ~BaseThread();

	void	Start();
	virtual void Update() = 0;

	void	PushMsg(ThreadMsg *msg);

	void	Exit(){ m_is_exit = true; }
	// 等待线程执行完毕
	void	Wait();

protected:
	std::thread		*m_thread;
	bool			m_is_exit;

	MsgQueue<ThreadMsg *> m_recv_queue;
	MsgQueue<ThreadMsg *> m_send_queue;
};

#endif 

