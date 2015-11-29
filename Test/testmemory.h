
#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H

#include <thread>
#include "lib/include/common/memoryvl.h"
#include "lib/include/common/mem.h"


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
				test[j] = Mem::Alloc((j + j + 1) * 2);
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
		for (int i = 0; i < thread_num; ++i)
		{
			t[i] = new std::thread(TestMemory::update, (void *)NULL);
		}

		for (int i = 0; i < thread_num; ++i)
		{
			t[i]->join();
		}
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
