
#include "dataqueue.h"

bool DataQueue::Push(const char *data, unsigned int length, void(*CallBack)(const char *data, unsigned int length))
{
	DataInfo info;
	info.data = data;
	info.length = length;
	info._CallBack = CallBack;
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
	info->_CallBack(info->data, info->length);
	return true;
}

