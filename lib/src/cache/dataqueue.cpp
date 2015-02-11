
#include "dataqueue.h"

DataQueue::DataQueue()
{

}

DataQueue::~DataQueue()
{

}

bool DataQueue::Push(const char *data, unsigned int length, CallBackFunc func)
{
	DataInfo info;
	info.data = data;
	info.length = length;
	info.func = func;
	return m_queue.Push(info);
}

bool DataQueue::Pop(char *data, unsigned int &length)
{
	if (m_queue.IsEmpty())
	{
		return false;
	}
	DataInfo *info = m_queue.Pop();
	data = (char *)info->data;
	length = info->length;
	return true;
}

bool DataQueue::Pop()
{
	if (m_queue.IsEmpty())
	{
		return false;
	}
	DataInfo *info = m_queue.Pop();
	if (info->func != NULL)
	{
		info->func(info->data, info->length);
	}
	return true;
}

