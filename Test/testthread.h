
#ifndef TEST_THREAD_H
#define TEST_THREAD_H

#include <thread>
#include "lib/include/common/mutex.h"
#include "lib/include/common/thread.h"

namespace TestThread
{
	std::mutex g_mutex;
	void thread1()
	{
		printf("thread__1\n");
		
		{
			MutexLock lock(&g_mutex);
			printf("thread__2\n");
		}
	}

	void * thread2(void *arpg)
	{
		printf("thread__1\n");

		{
			MutexLock lock(&g_mutex);
			printf("thread__2\n");
		}
		return NULL;
	}

	void Test1()
	{
		{
			MutexLock lock(&g_mutex);
			printf("test__1\n");
			Thread test_thread;
			test_thread.Create(thread2);
			//std::thread test_thread(thread1);
			
			printf("test__2\n");
			//test_thread.join();
		}
		//Sleep(2000);
	}
}

#endif