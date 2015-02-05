
#ifndef DATA_QUEUE_H
#define DATA_QUEUE_H

#include "common/datastructure/circlequeue.h"

/*
	只支持字符串，一般数据可以通过序列化成字符串来进行保存
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