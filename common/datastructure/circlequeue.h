
#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H

#include <stdlib.h>
#include <string.h>

/*
	��֧�ֶ��߳�
*/
template<class T>
class CircleQueue
{
public:
	CircleQueue(unsigned int size = 64):m_size((size <= 0) ? 1:size),m_head(0),m_tail(0)
	{
		m_queue = new T[m_size];
		// ���ﲻ����memset,��Ϊ���T����Ļ����Ὣ�ڲ������ṹ��0
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
		�� head ���� tail 
		* ����� head ׷�� tail Ϊ empty
		* ����� tail ׷�� head Ϊ full
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
	�������г�Աָ�����ʱ��memcpyֻ���ָ���ַ��һͬ���ƹ�����
	��˵�ԭ�������ݸı�ʱ�����������Ҳ��ı䣬����string��
	����Ҫ�������ؿ�������
	*/
	//memcpy(&m_queue[m_tail], &val, sizeof(T));
	m_queue[m_tail] = val;

	// ���ڿ��ܻ����·���ռ䣬m_tail�ᷢ���ı䣬��˲�����new_tail��ֵ
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
