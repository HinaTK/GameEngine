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
		//m_queue = (T *)malloc(m_size * sizeof(T));
		m_queue = new T[m_size];
		// ���ﲻ����memset,��Ϊ���T����Ļ����Ὣ�ڲ������ṹ��0
		// memset(m_queue, 0, m_size * sizeof(T));
	}

    ~CircleQueue()
	{
		//free(m_queue);
		delete[]m_queue;
	};
	bool	Push(T &val);

	unsigned int	Head();

	unsigned int	Tail();

	T *		Val();

	bool	IsEmpty();

	bool	Resize();

	void	Clear();

private:
	T *	m_queue;
	unsigned int	m_head;
	//volatile unsigned int	m_tail;
	unsigned int	m_tail;
	unsigned int	m_size;
};

template<class T>
void CircleQueue<T>::Clear()
{
	m_head = m_tail;
}



template<class T>
T * CircleQueue<T>::Val()
{
	return &m_queue[m_head++];
}

template<class T>
bool CircleQueue<T>::IsEmpty()
{
	if (m_tail == m_head )		// ͷβ���ʱ�����������Ѿ�Ϊ��
	{
		return true;
	}
	return false;
}


template<class T>
bool CircleQueue<T>::Resize()
{
	//T * newQueue = (T *)malloc((m_size<<1) * sizeof(T));
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
	//free(m_queue);
	delete[]m_queue;
	m_queue = newQueue;
	m_size = m_size<<1;
	return true;
}

template<class T>
bool CircleQueue<T>::Push( T &val )
{
	if (((m_tail + 1) % m_size) == m_head)		// �����Ѿ����ˣ���Ҫ���·����ڴ�
	{
		if (!Resize())
		{
			return false;
		}
	}
	/* 
		�������г�Աָ�����ʱ��memcpyֻ���ָ���ַ��һͬ���ƹ�����
		��˵�ԭ�������ݸı�ʱ�����������Ҳ��ı䣬����string
	*/
	//memcpy(&m_queue[m_tail], &val, sizeof(T));
	m_queue[m_tail] = val;
	// ����д�ǳ���Ҫ,��Ϊ��������дm_tail����ԭ�Ӳ���
	if ((m_tail + 1) >= m_size)
	{
		m_tail = 0;
	}
	else
	{
		++m_tail;
	}
	return true;
}


#endif
