
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
	void	Run();
	void	RecvMsg(unsigned char sid, int len, const char *data);
private:
};

#endif