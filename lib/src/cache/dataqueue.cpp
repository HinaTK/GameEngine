
#include "dataqueue.h"
#include "libcommon/memoryvl.h"

bool DataQueue::Push(const char *data, unsigned int length)
{
	MemoryVL::MemoryInfo info;
	MemoryVL::Instance().Malloc(length, info);
	m_queue.Push(data);
	return true;
}

