
#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <thread>
#include <string>
#include "threadmanager.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/frame/message.h"
#include "common/serverdef.h"

/*
	目的：以多线程并行代替多进程并行
*/

class ThreadManager;
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

	void		SetID(ThreadID id){ m_id = id; }
	ThreadID	GetID(){ return m_id; }

	virtual bool	Init(){ return true; }
	virtual bool	Ready(){ return true; }
	void	Start();

	void	Loop(bool sleep = true);

	void	PushMsg(ThreadMsg *msg);
	virtual void	CMD(short type, ThreadID sid, int len, const char *data){}
	ThreadManager *GetManager(){ return m_manager; }
	void	Exit();
	void	Wait();


	void 	SetSleepTime(unsigned short time){m_sleep_time = time;}
	void	SetName(char *name){m_name = name;}
	const char *	GetName(){ return m_name.c_str(); }
private:
	// 不允许复制
	BaseThread(const BaseThread&);
	void operator=(const BaseThread&);
protected:
	
	virtual bool	Run() = 0;
	virtual void	RecvData(short type, ThreadID sid, int len, const char *data) = 0;
protected:
	ThreadID		m_id;
	std::string		m_name;
	std::thread		*m_thread;
	ThreadManager	*m_manager;
	bool			m_is_start;
	bool			m_is_exit;

	MsgQueue<ThreadMsg *> m_recv_queue;
	unsigned short	m_sleep_time;
};

#endif 

