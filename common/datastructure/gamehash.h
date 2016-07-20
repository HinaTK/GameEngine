
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
	template<class K, class V>
	class Hash
	{
	public:
		Hash(unsigned int size = 256)
			: m_size((size <= 0) ? 1 : size)
		{
			m_hash_list = (KeyNode **)malloc(m_size * sizeof(KeyNode*));
			memset(m_hash_list, NULL, m_size * sizeof(KeyNode*));
		}

		virtual ~Hash()
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
					delete next_node;
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

		bool		Push(K key, V &val);
		void		Erase(K key);
		V &			operator[](K key);

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
				node = node->next;
			}
			return End();
		}

	protected:
		unsigned int	m_size;
		KeyNode			**m_hash_list;
		_Array			m_value_array;	// 所有数据保存的数据结构
		V				m_nil;
	};

	template<class K, class V>
	bool game::Hash<K, V>::Push(K key, V &val)
	{
		unsigned int real_key = key % m_size;

		KeyNode *node = new KeyNode;
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
				delete node;
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
				return *(m_value_array.Find(node->array_key));
			}
			node = node->next;
		}
		return m_nil;	
	}
}
#endif
