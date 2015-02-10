
#ifndef DATA_QUEUE_H
#define DATA_QUEUE_H

#include "common/datastructure/circlequeue.h"

/*
	*ֻ֧���ַ�����һ�����ݿ���ͨ�����л����ַ��������б���
*/

class DataQueue
{
public:
	DataQueue();
	~DataQueue();

	typedef void(*CallBack)(const char *data, unsigned int length);
	struct DataInfo
	{
		const char		*data;
		unsigned int	length;
		CallBack		_CallBack;
	};

	bool		Push(const char *data, unsigned int length, void(*CallBack)(const char *data, unsigned int length));

	bool		Pop(char *data, unsigned int &length);

private:
	CircleQueue<DataInfo> m_queue;
};

#endif