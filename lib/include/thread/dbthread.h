
#ifndef DB_THREAD_H
#define DB_THREAD_H

#include "basethread.h"

class DBThread : public BaseThread
{
public:
	~DBThread();
	DBThread(ThreadManager *manager);

	void	Update();
private:
};

#endif