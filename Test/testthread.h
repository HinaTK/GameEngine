
#ifndef TEST_THREAD_H
#define TEST_THREAD_H

#include "lib/include/thread/basethread.h"

class ThreadManager;
class TestThread2 : public BaseThread
{
public:
	TestThread2(ThreadManager *manager);
	~TestThread2();

	void	Run();
protected:
	void	Init();
};

#endif