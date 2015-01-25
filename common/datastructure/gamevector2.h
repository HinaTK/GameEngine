#ifndef GameVector2_H
#define GameVector2_H

template<class T>
class GameVector2
{
public:
	GameVector2(unsigned int size = 64):
	  m_size((size <= 0) ? 1:size),
	  m_handle(0)
	{
		m_list = (T *)malloc(m_size * sizeof(T));
		m_is_empty = (bool *)malloc(m_size * sizeof(bool));
		memset(m_is_empty, true, m_size * sizeof(bool));
	}
	~GameVector2()
	{
		free(m_list);
	}
	static const int INVALID_HANDLE = -1;

	unsigned int	Push(T &val);

	bool			Resize();

	void			Erase(unsigned int handle);

	T&		operator[](unsigned int index);
private:
	T *m_list;
	unsigned int m_handle;
	unsigned int m_size;
	bool *m_is_empty;
};

template<class T>
void GameVector2<T>::Erase( unsigned int handle )
{
	m_is_empty[handle] = true;
	if (handle >= m_handle - 1)
	{
		while(m_is_empty[m_handle - 1])
		{
			--m_handle;
		}
	}
}

template<class T>
bool GameVector2<T>::Resize()
{
	unsigned int newSize = (m_size<<1);
	T * newList = (T *)malloc( newSize * sizeof(T));
	bool * newIsEmpty = (bool *)malloc(newSize * sizeof(bool));
	if (newList == NULL || m_list == NULL || newIsEmpty == NULL)
	{
		return false;
	}
	memcpy(newList, m_list, m_size * sizeof(T));
	memcpy(newIsEmpty, m_is_empty, m_size * sizeof(bool));
	free(m_list);
	free(m_is_empty);
	m_list = newList;
	m_is_empty = newIsEmpty;
	m_size = newSize;
	return true;
}

template<class T>
unsigned int GameVector2<T>::Push( T &val )
{
	if (m_handle == m_size)
	{
		if (!Resize())
		{
			return GameVector<T>::INVALID_HANDLE;
		}	
	}
	m_list[m_handle] = val;
	m_is_empty[m_handle] = false;
	m_handle++;
	return m_handle - 1;
}

template<class T>
T& GameVector2<T>::operator[]( unsigned int index )
{
	if (index >= m_size)
	{
		T t;
		return t;
	}
	return m_list[index];
}

#endif