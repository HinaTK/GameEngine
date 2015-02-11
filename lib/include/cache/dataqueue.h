
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

	typedef void(*CallBackFunc)(const char *data, unsigned int length);
	struct DataInfo
	{
		const char		*data;
		unsigned int	length;
		CallBackFunc	func;
	};

	bool		Push(const char *data, unsigned int length, CallBackFunc func = NULL);

	bool		Pop(char *data, unsigned int &length);

	bool		Pop();

private:
	CircleQueue<DataInfo> m_queue;
};

#endif