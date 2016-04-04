
#ifndef DB_THREAD_H
#define DB_THREAD_H

#include "lib/include/thread/basethread.h"

class DBThread : public BaseThread
{
public:
	virtual ~DBThread();
	DBThread(ThreadManager *manager);

protected:
	void	Init();
	bool	Run();
	void	RecvData(short type, int sid, int len, const char *data);
private:
};

#endif