
#include "dataqueue.h"
#include "libcommon/memoryvl.h"

bool DataQueue::Push(const char *data, unsigned int length)
{
	//char *real_data = (char *)MemoryVL::Instance().Malloc(length);
	m_queue.Push(data);
	return true;
}

