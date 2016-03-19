
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
	void	Loop(bool sleep = true);

	void	PushMsg(ThreadMsg *msg);
	void	Exit();
	void	Wait();

	void	SetID(int id){ m_id = id; }
protected:
	virtual void	Init() = 0;
	virtual bool	Run() = 0;
	virtual void	RecvMsg(unsigned char sid, int len, const char *data) = 0;
	virtual void	CMD(unsigned char cmd, unsigned char sid, int len, const char *data){};
protected:
	int				m_id;
	ThreadManager	*m_manager;
	std::thread		*m_thread;
	bool			m_is_start;
	bool			m_is_exit;

	MsgQueue<ThreadMsg *> m_recv_queue;
};

#endif 

