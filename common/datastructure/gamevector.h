
#ifndef GAME_VECTOR_H
#define GAME_VECTOR_H

#include <stdlib.h>
#include <string.h>

/*
	Vector 与 std::vector的区别在于：
	Vector在删除数制的时候不在乎容器里面的数据顺序
	而std::vector需要移动数据
*/
namespace game
{
template<class T>
class Vector
{
public:

	Vector(unsigned int size = 64):m_size((size <= 0) ? 1:size),m_index(0)
	{
		m_list = new T[m_size];
		memset(m_list, NULL, m_size);
	}
	~Vector()
	{
		delete[]m_list;
	}
	static const int INVALID_HANDLE = -1;

	template<class V, class Handle = Vector>
	class Iterator
	{
		friend class Vector;
	public:
		Iterator() :m_index(0){}
		Iterator(unsigned int index, Handle *hadle = 0) :m_index(index), m_handle(hadle){}
		~Iterator(){}

		Iterator<V, Handle>& operator ++()
		{
			++m_index;
			return *this;
		}

		Iterator<V, Handle>& operator --()
		{
			--m_index;
			return *this;
		}

		V* operator->() { return &m_handle->m_list[m_index]; }
		V& operator*() { return m_handle->m_list[m_index];}

		bool operator==(const Iterator<V, Handle> &right) const { return (m_index == right.m_index && m_handle == right.m_handle); }
		bool operator!=(const Iterator<V, Handle> &right) const { return (m_index != right.m_index || m_handle != right.m_handle); }

		unsigned m_index;
	private:
		Handle *m_handle;
	};

	typedef Iterator<T> iterator;

	unsigned int	Push(T &val);

	void			Erase(T &val);

	bool			EraseIndex(unsigned int index);

	iterator		Begin(){ return iterator(0, this); }

	iterator		End(){ return iterator(m_index, this); }

	T&				Back(){ return m_list[m_index - 1]; }

	T&				operator[](unsigned int index);			// 要先判断是否存在Exist

	void			PopBack(){ --m_index; }					// m_index是否小于等于0由外部确保

	unsigned int	MaxSize(){ return m_size;};

	unsigned int	Size(){ return m_index;}

	bool			Exist(unsigned int index);

	void			Clear();

	bool			Init(unsigned int size);	// 初始化数据

protected:
	bool			Resize();
private:
	T * m_list;
	unsigned int m_size;		// 容器容量
	unsigned int m_index;		// 当前数据索引
};

template<class T>
T& Vector<T>::operator[]( unsigned int index )
{
	return m_list[index];
}

template<class T>
bool Vector<T>::Exist( unsigned int index )
{
	if (index >= m_index )
	{
		return false;
	}
	return true;
}

template<class T>
unsigned int Vector<T>::Push( T &val )
{
	if (m_index == m_size)
	{
		if (!Resize())
		{
			return Vector<T>::INVALID_HANDLE;
		}	
	}
	
	m_list[m_index++] = val;
	return m_index - 1;
}

template<class T>
void Vector<T>::Erase( T &val )
{
	for (unsigned int i = 0; i < m_index; ++i)
	{
		if (m_list[i] == val)
		{
			m_list[i] = m_list[m_index - 1];
			--m_index;
			break;
		}
	}
}

template<class T>
bool Vector<T>::EraseIndex(unsigned int index)
{
	if (index >= m_index)
	{
		return false;
	}
	m_list[index] = m_list[m_index - 1];
	--m_index;
	return true;
}

template<class T>
bool Vector<T>::Resize()
{
	unsigned int new_size = (m_size << 1);
	T *new_list = new T[new_size];
	if (new_list == NULL || m_list == NULL)
	{
		return false;
	}
	memset(new_list, NULL, new_size);
	memcpy(new_list, m_list, m_size * sizeof(T));
	delete[]m_list;
	m_list = new_list;
	m_size = new_size;
	return true;
}

template<class T>
void Vector<T>::Clear()
{
	m_index = 0;
}


template<class T>
bool game::Vector<T>::Init(unsigned int size)
{
	if (size < m_size)
	{
		return false;
	}
	m_index = size;
	return true;
}

}

#endif
