
#ifndef DB_THREAD_H
#define DB_THREAD_H

#include "basethread.h"

class DBThread : public BaseThread
{
public:
	~DBThread();
	DBThread();

	void	Update();
private:
};

#endif