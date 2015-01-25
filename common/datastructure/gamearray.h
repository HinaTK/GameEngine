
#ifndef GAME_ARRAY_H
#define GAME_ARRAY_H

#include <queue>
#include "gamevector.h"

/*
	array 不同于 vector,array始终以下标来查找数据，具有快速定位数据能力
	游戏中的作用：对象管理，网络连接管理
*/

namespace game
{
template<class T>
class Array
{
public:
	Array(unsigned int size = 64);
	~Array(){}

	template<class V, class Handle = Array>
	class Iterator
	{
		friend class Array;
	public:
		Iterator():m_index(0){}
		Iterator(unsigned int index, Handle *handle = 0) :m_index(index), m_handle(handle){}
		~Iterator(){}

		Iterator<V, Handle>& operator ++()
		{
			++m_index;
			while (m_index < m_handle->m_end.m_index && !m_handle->m_value[m_index].be_used)
			{
				++m_index;
			}
			return *this;
		}

		Iterator<V, Handle>& operator --()
		{
			--m_index;
			while (m_index >= m_handle->m_begin.m_index && !m_handle->m_value[m_index].be_used)
			{
				--m_index;
			}
			return *this;
		}

		V* operator->() { return &m_handle->m_value[m_index].val; }
		V& operator*() { return m_handle->m_value[m_index].val; }

		bool operator==(const Iterator<V, Handle> &right) const { return (m_index == right.m_index && m_handle == right.m_handle); }
		bool operator!=(const Iterator<V, Handle> &right) const { return (m_index != right.m_index || m_handle != right.m_handle); }

		unsigned m_index;
	private:
		Handle *m_handle;
	};

	typedef Iterator<T> iterator;

	struct ValueState
	{
		T		val;
		bool	be_used;
	};
	unsigned int	Insert(T &val);

	void			Erase(unsigned int index);

	bool			Erase(unsigned int index, T &val);

	bool			Exist(unsigned int index);

	bool			Exist(unsigned int index, T &val);

	unsigned int	Size(){ return m_size; }

	iterator		Begin(){ return m_begin; }

	iterator		End(){ return m_end; }

	iterator		Find(unsigned int index)
	{
		if (index < m_value.Size() && m_value[index].be_used)
		{
			return iterator(index, this);
		}
		return m_end;
	}

	// index 由外部保证
	T&				operator[](unsigned int index){ return m_value[index].val; }

	void			Clear();
private:
	Vector<ValueState>	m_value;
	std::queue<unsigned int> m_index_pool;
	iterator		m_begin;
	iterator		m_end;
	unsigned int	m_size;
};

template<class T>
Array<T>::Array(unsigned int size)
: m_value(size)
, m_size(0)
{
	m_begin.m_handle	= this;
	m_begin.m_index		= 0;
	m_end.m_handle		= this;
	m_end.m_index		= 0;
}

template<class T>
unsigned int Array<T>::Insert(T &val)
{
	unsigned int index = -1;
	ValueState vs = { val, true };
	if (m_index_pool.size() <= 0)
	{
		index = m_value.Size();
		m_value.Push(vs);
	}
	else
	{
		index = m_index_pool.front();
		m_index_pool.pop();
		m_value[index] = vs;
	}

	if (index < m_begin.m_index)
	{
		m_begin.m_index = index;
	}
	else if (index >= m_end.m_index)
	{
		m_end.m_index = index + 1;
	}
	++m_size;
	return index;
}

template<class T>
void Array<T>::Erase(unsigned int index)
{
	if (index >= m_value.Size() || !m_value[index].be_used)
	{
		return;
	}
	m_value[index].val.~T();
	m_value[index].be_used = false;
	m_index_pool.push(index);

	if (index == m_begin.m_index)
	{
		unsigned i = index + 1;
		for (; i < m_value.Size() && i < m_end.m_index; ++i)
		{
			if (m_value[i].be_used)
			{
				break;
			}
		}
		m_begin.m_index = i;
	}
	else if (index == (m_end.m_index - 1))
	{
		unsigned i = index - 1;
		for (; i > m_begin.m_index; --i)
		{
			if (m_value[i].be_used)
			{
				break;
			}
		}
		m_end.m_index = i;
	}
	--m_size;
}

template<class T>
bool Array<T>::Erase(unsigned int index, T &val)
{
	if (index >= m_value.Size() || !m_value[index].be_used)
	{
		return false;
	}

	val = m_value[index].val;
	//m_value[index].val.~T();
	m_value[index].be_used = false;
	m_index_pool.push(index);

	if (index == m_begin.m_index)
	{
		unsigned i = index + 1;
		for (; i < m_value.Size() && i < m_end.m_index; ++i)
		{
			if (m_value[i].be_used)
			{
				break;
			}
		}
		m_begin.m_index = i;
	}
	else if (index == (m_end.m_index - 1))
	{
		unsigned i = index - 1;
		for (; i > m_begin.m_index; --i)
		{
			if (m_value[i].be_used)
			{
				break;
			}
		}
		m_end.m_index = i;
	}
	--m_size;
	return true;
}

template<class T>
bool Array<T>::Exist(unsigned int index)
{
	if (index < m_value.Size() && m_value[index].be_used)
	{
		return true;
	}
	return false;
}

template<class T>
bool Array<T>::Exist(unsigned int index, T &val)
{
	if (index < m_value.Size() && m_value[index].be_used)
	{
		val = m_value[index].val;
		return true;
	}
	return false;
}

template<class T>
void Array<T>::Clear()
{
	m_value.Clear();
	m_begin.m_index = 0;
	m_end.m_index = 0;
}
}
#endif