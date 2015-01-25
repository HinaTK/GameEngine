
#ifndef THREAD_TEST_H
#define THREAD_TEST_H

#include "libcommon.h"

namespace ThreadTest
{

	void Text(MutexLock *l)
	{
		printf("fuck\n");
	}

	void Text1(MutexLock l)
	{
		printf("fuck\n");
	}
	Mutex mutex;

	void MutexTest()
	{
		{
			MutexLock l(&mutex);
			printf("fuck\n");
		}
		
		static int  i = 0;
		printf("i = %d\n", i);
		++i;
	}

	void *fun1(void *i)
	{
		int *j = (int *)i;
		int k = *j;
		for (int l = 0; l < 100; ++l)
		{
			printf("i = %d ,k = %d\n", *j, k);
		}
		return NULL;
	}
	int k = 0;
	void *fun2(void *i)
	{
		int *j = (int *)i;
		k = *j;
		for (int l = 0; l < 100; ++l)
		{
			printf("i = %d ,k = %d\n", *j, k);
		}
		return NULL;
	}

	//int k = 0;
	void *fun3(void *i)
	{
		int *j = (int *)i;
		MutexLock lock(&mutex);
		k = *j;
		
		for (int l = 0; l < 100; ++l)
		{
			printf("i = %d ,k = %d\n", *j, k);
		}
		return NULL;
	}
	void CreateThread()
	{
		// 该测试要证明，线程存在线程栈，也就是存在栈空间的变量不需要加锁
		Thread thread;
		int a = 0;
		int b = 1;
		int c = 2;
// 		thread.Create(fun1, &a);
// 		thread.Create(fun1, &b);
// 		thread.Create(fun1, &c);
// 
// 		thread.Create(fun2, &a);
// 		thread.Create(fun2, &b);
// 		thread.Create(fun2, &c);

		thread.Create(fun3, &a);
		thread.Create(fun3, &b);
		thread.Create(fun3, &c);

		system("pause");
	}
}


#endif