
#ifndef LIST_CACHE_INT_H
#define LIST_CACHE_INT_H

template<class T>
class ListCacheInt
{
public:
	ListCacheInt(unsigned int key);
	~ListCacheInt();

	struct ListNode
	{
		T val;
		ListNode *next;
	};

	bool	Push(T &val);
private:
	unsigned int m_key;
	unsigned int m_size;
};

template<class T>
ListCacheInt<T>::ListCacheInt(unsigned int key)
: m_key(key)
, m_size(0)
{

}
template<class T>
ListCacheInt<T>::~ListCacheInt()
{

}

#endif
