﻿
#ifndef DB_THREAD_H
#define DB_THREAD_H

#include "dbmanager.h"
#include "lib/include/thread/basethread.h"
#include "lib/include/db/fieldmanager.h"


class ThreadManager;
class DBThread : public BaseThread
{
public:
	virtual ~DBThread();
	DBThread(ThreadManager *thread_manager);

	FieldManager *	GetFieldManager(){ return &m_field_manager; }
protected:
	bool	Init();
	bool	Run();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	FieldManager 	m_field_manager;
	DBManager		m_db_manager;
	
};

#endif