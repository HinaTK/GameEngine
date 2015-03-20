
#ifndef DATA_QUEUE_H
#define DATA_QUEUE_H

#include "common/datastructure/circlequeue.h"
#include "database.h"

/*
	*ֻ֧���ַ�����һ�����ݿ���ͨ�����л����ַ��������б���
*/

class DataQueue : public CacheBase
{
public:
	DataQueue();
	~DataQueue();

	struct DataInfo
	{
		const char		*data;
		unsigned int	length;
	};

	bool		Push(const char *data, unsigned int length);

	bool		Pop(char *data, unsigned int &length);

	bool		Pop();

private:
	CircleQueue<DataInfo> m_queue;
};

#endif