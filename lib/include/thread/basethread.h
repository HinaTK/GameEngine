
#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <thread>
#include <string>
#include "threadmanager.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/message.h"
#include "common/serverdef.h"

#define THREAD_RUNNING	true;
#define THREAD_IDLING	false;

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
	virtual void	Exit(){}

	inline void	SendMsg(ThreadID did, TPT type, int len, const char *data){m_manager->SendMsg(did, type, len, data, m_id);}
	inline void SendMsg(ThreadID did, ThreadClass * tc){m_manager->SendMsg(did, tc);}
	template<class T>
	inline void SendMsg(ThreadID did, TPT type, T data){m_manager->SendMsg(did, type, data, m_id);}

	void	PushMsg(ThreadMsg &msg);
	void	SysCmd(ThreadMsg &msg);
	virtual bool 	CMD(TPT type, ThreadID sid, int len, const char *data){ return false; }
	ThreadManager *GetManager(){ return m_manager; }
	MsgMemoryManager *GetMemory(){return &m_msg_memory;}
	void	DoExit();
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

