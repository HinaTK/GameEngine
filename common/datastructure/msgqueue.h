
#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <mutex>
#include "gamequeue.h"

/*
	单一线程访问Pop,则线程安全
*/
template<class T>
class MsgQueue
{
public:
	MsgQueue(unsigned int size = 64)
	{
		m_write_queue = new game::Queue<T>(size);
		m_read_queue = new game::Queue<T>(size);
	}
	~MsgQueue()
	{
		delete m_write_queue;
		delete m_read_queue;
	}

	bool Push(T val)
	{
		m_write_mutex.lock();
		bool ret = m_write_queue->Push(val);
		m_write_mutex.unlock();
		return ret;
	}

	bool Pop(T &val/*, int tt*/)
	{
		if (m_read_queue->Pop(val))
		{
			return true;
		}
		
		game::Queue<T> *temp = m_read_queue;
		m_write_mutex.lock();
// 		if (tt > 0 && tt < 100)
// 		{
// 			printf("m_write_queue ....... %d \n", tt);
// 			m_write_queue->Show();
// 			printf("m_read_queue ....... %d \n", tt);
// 			m_read_queue->Show();
// 		}
		m_read_queue = m_write_queue;
		m_write_queue = temp;
		m_write_mutex.unlock();

		return false;
	}

private:
	game::Queue<T>	*m_write_queue;
	game::Queue<T>	*m_read_queue;
	std::mutex		m_write_mutex;
};

#endif