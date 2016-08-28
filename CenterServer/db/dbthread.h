
#ifndef DB_THREAD_H
#define DB_THREAD_H

#include "lib/include/thread/basethread.h"
#include "dbmanager.h"

class DBThread : public BaseThread
{
public:
	virtual ~DBThread();
	DBThread(ThreadManager *manager);

protected:
	bool	Init();
	bool	Run();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
	bool 	CMD(TPT type, ThreadID sid, int len, const char *data);
private:

	DBManager	m_db_manager;
};

#endif