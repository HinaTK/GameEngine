#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H

#include <stdlib.h>
#include <string.h>

template<class T>
class CircleQueue
{
public:
	CircleQueue(unsigned int size = 64):m_size((size <= 0) ? 1:size),m_head(0),m_tail(0)
	{
		m_queue = new T[m_size];
		// 这里不可以memset,因为如果T是类的话，会将内部的类表结构置0
		// memset(m_queue, 0, m_size * sizeof(T));
	}

    ~CircleQueue()
	{
		delete[]m_queue;
	};
	bool	Push(T &val);

	T *		Pop();

	unsigned int	Head();

	unsigned int	Tail();
	
	bool	IsEmpty();

	void	Clear();

protected:
	bool	Resize();

private:
	T *	m_queue;
	unsigned int	m_head;
	unsigned int	m_tail;
	unsigned int	m_size;
};

template<class T>
void CircleQueue<T>::Clear()
{
	m_head = m_tail;
}

template<class T>
T * CircleQueue<T>::Pop()
{
	if (m_head >= m_size)
	{
		m_head -= m_size;
	}
	return &m_queue[m_head++];
}

template<class T>
bool CircleQueue<T>::IsEmpty()
{
	if (m_tail == m_head )		// 头尾相等时，表明队列已经为空
	{
		return true;
	}
	return false;
}

template<class T>
bool CircleQueue<T>::Resize()
{
	T *newQueue = new T[(m_size << 1)];
	if (newQueue == NULL || m_queue == NULL)
	{
		return false;
	}

	memset(newQueue, 0, (m_size<<1) * sizeof(T));
	unsigned int tailSize = m_tail + 1;
	unsigned int headSize = m_size - m_head;
	memcpy(newQueue, m_queue + tailSize, headSize * sizeof(T));
	memcpy(newQueue + headSize, m_queue, tailSize * sizeof(T));
	delete[]m_queue;
	m_queue = newQueue;
	m_size = m_size<<1;
	return true;
}

template<class T>
bool CircleQueue<T>::Push( T &val )
{
	unsigned int new_tail = m_tail + 1;
	if (new_tail >= m_size)
	{
		new_tail -= m_size;
	}
	if (new_tail == m_head)
	{
		// 队列已经满了，需要重新分配内存
		if (!Resize())
		{
			return false;
		}
	}
	
	/* 
		当类中有成员指针变量时，memcpy只会把指针地址，一同复制过来。
		因此当原来的数据改变时，这里的数据也会改变，例如string。
		这里要求类重载拷贝函数
	*/
	//memcpy(&m_queue[m_tail], &val, sizeof(T));
	m_queue[m_tail] = val;
	m_tail = new_tail;
	return true;
}
#endif
