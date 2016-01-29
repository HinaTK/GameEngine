
#ifndef DB_THREAD_H
#define DB_THREAD_H

#include "lib/include/thread/basethread.h"

class DBThread : public BaseThread
{
public:
	~DBThread();
	DBThread(ThreadManager *manager);

	void	Run();

protected:
	void	Init();
private:
};

#endif