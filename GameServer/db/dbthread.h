
#ifndef DB_THREAD_H
#define DB_THREAD_H

#include "lib/include/thread/basethread.h"

class ThreadManager;
class DBThread : public BaseThread
{
public:
	virtual ~DBThread();
	DBThread(ThreadManager *thread_manager);

protected:
	bool	Init();
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	
};

#endif