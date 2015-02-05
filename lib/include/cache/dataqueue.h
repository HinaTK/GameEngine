
#ifndef DATA_QUEUE_H
#define DATA_QUEUE_H

#include "common/datastructure/circlequeue.h"

/*
	ֻ֧���ַ�����һ�����ݿ���ͨ�����л����ַ��������б���
*/

class DataQueue
{
public:
	DataQueue();
	~DataQueue();

	bool		Push(const char *data, unsigned int length);

	bool		Pop();

private:
	CircleQueue<const char *> m_queue;

};

#endif