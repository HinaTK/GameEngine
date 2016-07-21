
#ifndef DB_THREAD_H
#define DB_THREAD_H

#include "lib/include/thread/basethread.h"

class DBThread : public BaseThread
{
public:
	virtual ~DBThread();
	DBThread(ThreadManager *manager);

protected:
	void	Init(void *arg);
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
};

#endif