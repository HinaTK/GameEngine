
#ifndef DATA_QUEUE_H
#define DATA_QUEUE_H

#include "common/datastructure/circlequeue.h"

class DataQueue
{
public:
	DataQueue();
	~DataQueue();

	bool		Push(const char *data, unsigned int length);



private:
	CircleQueue<const char *> m_queue;

};

#endif