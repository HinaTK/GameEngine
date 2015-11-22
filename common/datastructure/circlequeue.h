
#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H

#include <stdlib.h>
#include <string.h>

/*
	不支持多线程
*/
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

	void	Clear();

protected:
	/*
		当 head 等于 tail 
		* 如果是 head 追上 tail 为 empty
		* 如果是 tail 追上 head 为 full
	*/

	bool	Resize();

private:
	T *	m_queue;
	unsigned int	m_size;
	unsigned int	m_head;
	unsigned int	m_tail;
};

template<class T>
void CircleQueue<T>::Clear()
{
	m_head = m_tail;
}

template<class T>
bool CircleQueue<T>::Push(T &val)
{
	unsigned int new_tail = m_tail + 1;
	if (new_tail >= m_size)
	{
		new_tail -= m_size;
	}

	if (new_tail == m_head)
	{
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

	// 由于可能会重新分配空间，m_tail会发生改变，因此不能用new_tail赋值
	m_tail = m_tail + 1;
	if (m_tail >= m_size)
	{
		m_tail -= m_size;
	}
	return true;
}

template<class T>
T * CircleQueue<T>::Pop()
{
	T *temp = NULL;

	if (m_tail == m_head)
	{
		return temp;
	}

	temp = &m_queue[m_head++];

	if (m_head >= m_size)
	{
		m_head -= m_size;
	}
	return temp;
}

template<class T>
bool CircleQueue<T>::Resize()
{
	T *newQueue = new T[(m_size << 1)];
	if (newQueue == NULL)
	{
		return false;
	}

	memset(newQueue, 0, (m_size<<1) * sizeof(T));
	if (m_tail >= m_head)
	{
		m_tail -= m_head;
		memcpy(newQueue, m_queue + m_head, m_tail * sizeof(T));
	}
	else
	{	
		memcpy(newQueue, m_queue + m_head, (m_size - m_head) * sizeof(T));
		memcpy(newQueue + m_size - m_head, m_queue, m_tail * sizeof(T));
		m_tail = m_size - m_head + m_tail;
	}
	m_head = 0;
	delete[]m_queue;
	m_queue = newQueue;
	m_size = m_size<<1;
	return true;
}

#endif
