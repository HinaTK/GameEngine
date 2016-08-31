﻿
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
	BaseThread(ThreadManager *manager, char exit = ThreadManager::EXIT_NORMAL);
	virtual ~BaseThread();

	void		SetID(ThreadID id){ m_id = id; }
	ThreadID	GetID(){ return m_id; }

	void			Start();
	void			Do();
	virtual bool	Init(){ return true; }
	virtual void	Ready(){}

	void	PushMsg(ThreadMsg &msg);
	void	SysCmd(ThreadMsg &msg);
	virtual bool 	CMD(TPT type, ThreadID sid, int len, const char *data){ return false; }
	ThreadManager *GetManager(){ return m_manager; }
	MsgMemoryManager *GetMemory(){return &m_msg_memory;}
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
	void			Loop(bool sleep = true);
	virtual bool	Run() = 0;
	virtual void	RecvData(TPT type, ThreadID sid, int len, const char *data) = 0;
protected:
	ThreadID		m_id;
	std::string		m_name;
	std::thread		*m_thread;
	ThreadManager	*m_manager;
	bool			m_is_start;
	bool			m_is_exit;

	MsgQueue<ThreadMsg> m_recv_queue;
	MsgMemoryManager	m_msg_memory;
	unsigned short	m_sleep_time;
};

#endif 

