
#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include "common/systemdef.h"
#include <mutex>
#include "gamelist.h"
#include "circlequeue.h"

// class MsgQueue
// {
// public:
// 	MsgQueue() :m_msg_queue(1024){}
// 	~MsgQueue(){};
// 
// 
// 	bool Push(SOCKET sock, const char *msg, unsigned int length)
// 	{
// 		GameMsg *m = new GameMsg(sock, msg, length);
// 		return m_msg_queue.Push(m);
// 	}
// 
// 	// bool IsEmpty(){ return m_msg_queue.IsEmpty(); }
// 
// 	GameMsg ** Pop()
// 	{
// 		return m_msg_queue.Pop();
// 	}
// 
// private:
// 
// 	CircleQueue<GameMsg *> m_msg_queue;
// };

template<class T>
class MsgQueue
{
public:
	MsgQueue(unsigned int size = 64)
	{
		m_write_queue = new game::List<T>(size);
		m_read_queue = new game::List<T>(size);
	}
	~MsgQueue(){}

	bool Push(T &val)
	{
		m_write_mutex.lock();
		bool ret = m_write_queue->PushBack(val);
		m_write_mutex.unlock();
		return ret;
	}

	// 找不到数据时，可适当睡眠
	bool Pop(T &val)
	{
		if (m_read_queue->PopFront(val))
		{
			return true;
		}
		game::List<T> *temp = m_read_queue;
		m_write_mutex.lock();
		m_read_queue = m_write_queue;
		m_write_queue = temp;
		m_write_mutex.unlock();

		if (m_read_queue->PopFront(val))
		{
			return true;
		}
		return false;
	}

private:
	game::List<T>	*m_write_queue;
	game::List<T>	*m_read_queue;
	std::mutex		m_write_mutex;
};

#endif