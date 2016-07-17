
#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H

#include <thread>
#include "lib/include/common/memoryvl.h"
#include "lib/include/common/mem.h"
#include "lib/include/common/memorypool.h"


class TT
{
public:

	void *		operator new(size_t c);
	void		operator delete(void *m);

	int a;
	char d;
	short c[32];
};

class TT2
{
public:

	int a;
	char d;
	short c[32];
};

namespace TestMemory
{
	void update(void *arg)
	{
		static const int test_num = 10;
		char *test[test_num];
		for (int i = 0; i < 1000; ++i)
		{
			for (int j = 0; j < test_num; ++j)
			{
                int val = (i + i + 1) * 2;
                test[j] = Mem::Alloc(val);
			}

			for (int j = 0; j < test_num; ++j)
			{
				Mem::Free(test[j]);
			}
		}
	}

	void Test1()
	{
		static const int thread_num = 3;
		std::thread *t[thread_num];
        t[0] = new std::thread(TestMemory::update, (void *)NULL);
        t[0]->join();

        for (int i = 1; i < thread_num; ++i)
		{
			t[i] = new std::thread(TestMemory::update, (void *)NULL);
		}

        for (int i = 1; i < thread_num; ++i)
		{
			t[i]->join();
		}
	}

	void Test2()
	{
		unsigned long begin = GetTickCount();
		for (int i = 0; i < 1000000; ++i)
		{
			TT *t = new TT();
			delete t;
		}
		printf("%d ms\n", GetTickCount() - begin);
	}

	void Test3()
	{
		unsigned long begin = GetTickCount();
		for (int i = 0; i < 1000000; ++i)
		{
			TT2 *t = new TT2();
			delete t;
		}
		printf("%d ms\n", GetTickCount() - begin);
	}

	void TestMemoryVL()
	{
// 		MemoryVL::MemoryInfo info;
// 		MemoryVL::Instance().Malloc(sizeof(int), info);
// 		*((int*)info.mem) = 12;
// 		MemoryVL::Instance().Free(info);
	}
}

#endif
