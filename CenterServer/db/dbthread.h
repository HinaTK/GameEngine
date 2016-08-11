
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
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
	bool 	CMD(short type, ThreadID sid, int len, const char *data);
private:

	DBManager	m_manager;
};

#endif