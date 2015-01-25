
#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H

#include "libcommon/memoryvl.h"

namespace TestMemory
{
	void TestMemoryVL()
	{
		MemoryVL::MemoryInfo info;
		MemoryVL::Instance().Malloc(sizeof(int), info);
		*((int*)info.mem) = 12;
		MemoryVL::Instance().Free(info);
	}
}

#endif
