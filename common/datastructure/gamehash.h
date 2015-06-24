
#ifndef GAME_HASH_H
#define GAME_HASH_H

#include "lib/include/common/memorypool.h"
#include "lib/include/common/mem.h"
#include "gamearray.h"

/*
	* 散列
	* key只支持基本数据类型，不支持浮点型，结构体和类
	* 可以通过序列化来将浮点型，结构体和类转化成字符串，从而得到支持
*/

namespace game
{
static const unsigned int HASH_MAX_KEY_LEN = 128;

static unsigned int _RealKey(const char *key, unsigned int length)
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

template<class K, class V>
class HashBase
{
public:
	HashBase(unsigned int size)
		: m_size((size <= 0) ? 1 : size)
		, m_memory_pool(sizeof(KeyNode), m_size)
	{
		m_hash_list = (KeyNode **)malloc(m_size * sizeof(KeyNode*));
		memset(m_hash_list, NULL, m_size * sizeof(KeyNode*));
	}

	virtual ~HashBase()
	{
		for (unsigned int i = 0; i < m_size; ++i)
		{
			if (m_hash_list[i] == NULL)
			{
				continue;
			}
			KeyNode *next_node = m_hash_list[i];
			KeyNode *temp_node = NULL;
			do 
			{
				temp_node = next_node->next;
				m_memory_pool.Free(next_node);
				next_node = temp_node;
			} while (next_node != NULL);
		}
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

	V			Nil(){ return m_nil; }
	iterator	Begin(){ return m_value_array.Begin(); }
	iterator	End(){ return m_value_array.End(); }

protected:
	unsigned int	m_size;
	KeyNode			**m_hash_list;
	_Array			m_value_array;	// 所有数据保存的数据结构
	MemoryPool		m_memory_pool;
	V				m_nil;
};

/************************************************
	key不是字符串
*************************************************/
template<class K, class V>
class Hash : public HashBase<K, V>
{
public:
	Hash(unsigned int size = 256): HashBase(size){}
	virtual ~Hash(){}

	bool		Push(K key, V &val);
	void		Erase(K key);
	V &			operator[](K key);

	iterator	Find(K key)
	{
		unsigned int real_key = key % m_size;
		KeyNode *node = m_hash_list[real_key];
		if (node != NULL && node->key == key)
		{
			return m_value_array.Find(node->array_key);
		}
		return End();
	}
};

template<class K, class V>
bool game::Hash<K, V>::Push(K key, V &val)
{
	unsigned int real_key = key % m_size;

	KeyNode *node = (KeyNode *)m_memory_pool.Alloc();
	node->key = key;
	node->array_key = m_value_array.Insert(val);

	// 若头结点为空，插入结点放置到头结点；否则插入结点成为新头结点
	if (m_hash_list[real_key] == NULL)
	{
		node->next = NULL;
	}
	else
	{
		node->next = m_hash_list[real_key];
	}

	m_hash_list[real_key] = node;
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
	key 是字符串
*************************************************/
template<class V>
class Hash<const char *, V> : public HashBase<char *, V>
{
public:
	Hash(unsigned int size = 256) : HashBase(size){}
	virtual ~Hash(){}

	bool	Push(const char *key, V &val, unsigned int key_len = 0);
	V &		Val(const char *key, unsigned int key_len = 0);
	V &		operator[](const char *key){ return Val(key); };
};

template<class V>
bool game::Hash<const char *, V>::Push(const char *key, V &val, unsigned int key_len)
{
	if (key_len == 0)
	{
		key_len = (unsigned int)strlen(key);
	}
	if (key_len > HASH_MAX_KEY_LEN)
	{
		return false;
	}
	unsigned int _key = _RealKey(key, key_len);
	unsigned int real_key = _key % m_size;

	KeyNode *node = (KeyNode *)m_memory_pool.Alloc();
	node->key = Mem::Alloc(key_len);
	memcpy(node->key, key, key_len);
	node->array_key = m_value_array.Insert(val);

	// 若头结点为空，插入结点放置到头结点；否则插入结点成为新头结点
	if (m_hash_list[real_key] == NULL)
	{
		node->next = NULL;
	}
	else
	{
		node->next = m_hash_list[real_key];
	}

	m_hash_list[real_key] = node;
	return true;
}

template<class V>
V & game::Hash<const char *, V>::Val(const char *key, unsigned int key_len /*= 0*/)
{
	if (key_len == 0)
	{
		key_len = (unsigned int)strlen(key);
	}
	if (key == NULL) return m_nil;

	if (key_len > HASH_MAX_KEY_LEN) return m_nil;

	KeyNode *node = NULL;
	unsigned int _key = _RealKey(key, key_len);
	unsigned int real_key = _key % m_size;

	node = m_hash_list[real_key];
	while (node != NULL)
	{
		if (memcmp(node->key, key, key_len) == 0)
		{
			goto HASVAL;
		}
		node = node->next;
	}
	return m_nil;
HASVAL:;
	return *(m_value_array.Find(node->array_key));
}
}

#endif