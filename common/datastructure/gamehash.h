
#ifndef GAME_HASH_H
#define GAME_HASH_H

#include "libcommon/memorypool.h"
#include "libcommon/memoryvl.h"
#include "gamearray.h"

/*
	* 散列
	* key只支持基本数据类型，不支持结构体和类
*/

namespace game
{
unsigned int _RealKey(const char *key, unsigned int length)
{
	static unsigned int real_key;
	real_key = 0;
	for (unsigned int i = 0; i < length && i < 4; ++i)
	{
		real_key = (real_key << 8);
		real_key = real_key + (0 | key[i]);
	}
	return real_key;
}

#define HASH_HEADER()\
	Hash(unsigned int size = 256)\
	: m_size((size <= 0) ? 1 : size)\
	, m_memory_pool(sizeof(ListNode), m_size)\
	{\
			m_hash_list = (ListNode **)malloc(m_size * sizeof(ListNode*));\
			memset(m_hash_list, NULL, m_size * sizeof(ListNode*));\
	}\
	~Hash()\
	{\
		free(m_hash_list);\
	}



template<class K, class V>
class Hash
{
public:
	Hash(unsigned int size = 256)
		: m_size((size <= 0) ? 1 : size)
		, m_memory_pool(sizeof(KeyNode), m_size)
	{
		m_hash_list = (KeyNode **)malloc(m_size * sizeof(KeyNode*));
		memset(m_hash_list, NULL, m_size * sizeof(KeyNode*));
	}
	~Hash()
	{
		free(m_hash_list); 
	}

	struct KeyNode
	{
		K				key;
		unsigned int	array_key;
		KeyNode			*next;
	};

	typedef Array<V> _Array;
	typedef typename _Array::iterator iterator;

	bool		Push(K key, V &val);
	void		Erase(K key);
	V &			operator[](K key);
	V			Nil(){ return m_nil; }

	iterator	Find(K key)
	{
		unsigned int real_key = key % m_size;
		KeyNode *node = m_hash_list[real_key];
		while (node != NULL)
		{
			if (node->key == key)
			{
				return m_value_array.Find(node->array_key);
			}
		}
		return End();
	}
	iterator	Begin(){ return m_value_array.Begin(); }
	iterator	End(){ return m_value_array.End(); }
private:
	unsigned int	m_size;
	KeyNode			**m_hash_list;
	_Array			m_value_array;
	MemoryPool		m_memory_pool;
	V				m_nil;
};

template<class K, class V>
bool game::Hash<K, V>::Push(K key, V &val)
{
	unsigned int real_key = key % m_size;

	if (m_hash_list[real_key] == NULL)
	{
		m_hash_list[real_key] = (KeyNode *)m_memory_pool.Alloc();
		m_hash_list[real_key]->key = key;
		m_hash_list[real_key]->array_key = m_value_array.Insert(val);
		m_hash_list[real_key]->next = NULL;
	}
	else
	{
		KeyNode *node = (KeyNode *)m_memory_pool.Alloc();
		node->key = real_key;
		node->array_key = m_value_array.Insert(val);
		node->next = m_hash_list[real_key];
		m_hash_list[real_key] = node;
	}
	return true;
}

template<class K, class V>
void game::Hash<K, V>::Erase(K key)
{
	unsigned int real_key = key % m_size;
	KeyNode *node = m_hash_list[real_key];
	KeyNode *frontNode = NULL;
	while (node != NULL)
	{
		if (node->key == key)
		{
			if (frontNode != NULL)
			{
				frontNode->next = node->next;	
			}
			else
			{
				// 删除的是头结点
				m_hash_list[real_key] = node->next;
			}
			m_value_array.Erase(node->array_key);
			m_memory_pool.Free(node);
			break;
		}
		frontNode = node;
		node = node->next;
	}
}

template<class K, class V>
V & game::Hash<K, V>::operator[](K key)
{
	unsigned int real_key = key % m_size;
	KeyNode *node = m_hash_list[real_key];

	while (node != NULL)
	{
		if (node->key == key)
		{
			goto HASVAL;
		}
		node = node->next;
	}
	return m_nil;
HASVAL:;
	return *(m_value_array.Find(node->array_key));
}



/************************************************
	key和val 都是是字符串
*************************************************/
template<>
class Hash<const char*, const char*>
{
public:
	HASH_HEADER();

	struct ListNode
	{
		MemoryVL::MemoryInfo key;
		MemoryVL::MemoryInfo val;
		ListNode *next;
	};

	template<class V, class Handle = Hash>
	class Iterator
	{
		friend class Hash;
	public:
		Iterator(unsigned int _index = 0, ListNode *_node = NULL, Handle *handle = NULL)
			: index(_index)
			, node(_node)
			, m_handle(handle)
		{
		}
		~Iterator(){}

		Iterator<V, Handle>& operator ++()
		{
			while (1)
			{
				if (node->next != NULL)
				{
					node = node->next;
					break;
				}
				++index;
				if (index >= m_handle->m_size)
				{
					break;
				}
				node = m_handle->m_hash_list[index];
			}

			return *this;
		}

		V* operator->() { return &node->val.mem; }
		V& operator*() { return node->val.mem; }

		bool operator==(const Iterator<V, Handle> &right) const { return (index == right.index && m_handle == right.m_handle); }
		bool operator!=(const Iterator<V, Handle> &right) const { return (index != right.index || m_handle != right.m_handle); }

		unsigned int index;
		ListNode *node;
	private:
		Handle *m_handle;
	};

	typedef Iterator<char*> iterator;

	bool	Push(const char* key, const char *val, int len = 0)
	{
		if (len < 0)
		{
			return false;
		}
		else if (len == 0)
		{
			len = (int)strlen(val) + 1;
		}

		unsigned int key_len = (unsigned int)strlen(key);
		if (len > 32)
		{
			return false;
		}
		unsigned int real_key = _RealKey(key, key_len);

		unsigned int index = real_key % m_size;

		if (m_hash_list[index] == NULL)
		{
			m_hash_list[index] = (ListNode *)m_memory_pool.Alloc();
			MemoryVL::Instance().Malloc(key_len, m_hash_list[index]->key);
			memcpy(m_hash_list[index]->key.mem, key, key_len);
			MemoryVL::Instance().Malloc(len, m_hash_list[index]->val);
			memcpy(m_hash_list[index]->val.mem, val, len);
			m_hash_list[index]->val.mem[len] = 0;
			m_hash_list[index]->next = NULL;
		}
		else
		{
			ListNode *node = (ListNode *)m_memory_pool.Alloc();
			MemoryVL::Instance().Malloc(key_len, node->key);
			memcpy(node->key.mem, key, key_len);
			MemoryVL::Instance().Malloc(len, node->val);
			memcpy(node->val.mem, val, len);
			node->val.mem[len] = 0;
			node->next = m_hash_list[index];
			m_hash_list[index] = node;
		}
		return true;
	}
	void	Erase(const char* key);

	const char* 	operator[](const char* key)
	{
		if (key == NULL)
		{
			return m_nil;
		}
		static ListNode *node = NULL;
		unsigned int len = (unsigned int)strlen(key);
		if (len > 32)
		{
			return m_nil;
		}
		unsigned int real_key = _RealKey(key, len);
		unsigned int index = real_key % m_size;

		node = m_hash_list[index];
		while (node != NULL)
		{
			if (memcmp(node->key.mem, key, len) == 0)
			{
				goto HASVAL;
			}
			node = node->next;
		}
		return m_nil;
	HASVAL:;
		return (node->val.mem);
	}

	const char*		Nil(){ return m_nil; }

	iterator	Begin(){ return iterator(0, m_hash_list[0], this); }
	iterator	End(){ return iterator(m_size - 1, NULL, this); }

private:
	unsigned int	m_size;
	ListNode		**m_hash_list;
	MemoryPool		m_memory_pool;
	const char*		m_nil;
};


/************************************************
	val 是字符串
*************************************************/
template<class K>
class Hash<K, const char*>
{
public:
	HASH_HEADER();

	struct ListNode
	{
		K key;
		MemoryVL::MemoryInfo val;
		ListNode *next;
	};

	bool	Push(K key, const char *val, int len = 0);
	void	Erase(K key);

	const char* 	operator[](K key);

	const char*		Nil(){ return m_nil; }

private:
	unsigned int	m_size;
	ListNode		**m_hash_list;
	MemoryPool		m_memory_pool;
	const char*		m_nil;
};


template<class K>
bool game::Hash<K, const char*>::Push(K key, const char *val, int len /*= 0*/)
{
	if (len < 0)
	{
		return false;
	}
	else if (len == 0)
	{
		len = (int)strlen(val) + 1;
	}

	unsigned int index = key % m_size;

	if (m_hash_list[index] == NULL)
	{
		m_hash_list[index] = (ListNode *)m_memory_pool.Alloc();
		m_hash_list[index]->key = key;
		MemoryVL::Instance().Malloc(len, m_hash_list[index]->val);
		memcpy(m_hash_list[index]->val.mem, val, len);
		m_hash_list[index]->val.mem[len] = 0;
		m_hash_list[index]->next = NULL;
	}
	else
	{
		ListNode *node = (ListNode *)m_memory_pool.Alloc();
		node->key = key;
		MemoryVL::Instance().Malloc(len, node->val);
		memcpy(node->val.mem, val, len);
		node->val.mem[len] = 0;
		node->next = m_hash_list[index];
		m_hash_list[index] = node;
	}

	return true;
}


template<class K>
void game::Hash<K, const char*>::Erase(K key)
{
	
}
template<class K>
const char* game::Hash<K, const char*>::operator[](K key)
{
	unsigned int index = key % m_size;

	ListNode *node = m_hash_list[index];
	while (node != NULL)
	{
		if (node->key == key)
		{
			goto HASVAL;
		}
		node = node->next;
	}
	return m_nil;
HASVAL:;
	return (node->val.mem);
}


/************************************************
	key 是字符串
*************************************************/
template<class V>
class Hash<const char *, V>
{
public:
	HASH_HEADER();

	bool	Push(const char *key, V &val);

	V &		operator[](const char *key);
	struct ListNode
	{
		MemoryVL::MemoryInfo key;
		V val;
		ListNode *next;
	};

private:
	unsigned int	m_size;
	ListNode		**m_hash_list;
	MemoryPool		m_memory_pool;
	V				m_nil;
};


template<class V>
bool game::Hash<const char *, V>::Push(const char *key, V &val)
{
	unsigned int len = (unsigned int)strlen(key);
	if (len > 32)
	{
		return false;
	}
	unsigned int real_key = _RealKey(key, len);

	unsigned int index = real_key % m_size;

	if (m_hash_list[index] == NULL)
	{
		m_hash_list[index] = (ListNode *)m_memory_pool.Alloc();
		MemoryVL::Instance().Malloc(len, m_hash_list[index]->key);
		memcpy(m_hash_list[index]->key.mem, key, len);
		m_hash_list[index]->val = val;
		//memcpy(&m_hash_list[index]->val, &val, sizeof(V));
		m_hash_list[index]->next = NULL;
	}
	else
	{
		ListNode *node = (ListNode *)m_memory_pool.Alloc();
		MemoryVL::Instance().Malloc(len, node->key);
		memcpy(node->key.mem, key, len);
		node->val = val;
		//memcpy(&node->val, &val, sizeof(V));
		node->next = m_hash_list[index];
		m_hash_list[index] = node;
	}

	return true;
}

template<class V>
V & game::Hash<const char *, V>::operator[](const char *key)
{
	if (key == NULL)
	{
		return m_nil;
	}
	static ListNode *node = NULL;
	unsigned int len = (unsigned int)strlen(key);
	if (len > 32)
	{
		return m_nil;
	}
	unsigned int real_key = _RealKey(key, len);
	unsigned int index = real_key % m_size;
	
	node = m_hash_list[index];
	while (node != NULL)
	{
		if (memcmp(node->key.mem, key, len) == 0)
		{
			goto HASVAL;
		}
		node = node->next;
	}
	return m_nil;
HASVAL:;
	return (node->val);
}
}

#endif