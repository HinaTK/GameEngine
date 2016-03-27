
#ifndef GAME_HASH_SET_H
#define GAME_HASH_SET_H

/*
	* 散列集
	* key只支持基本数据类型，不支持浮点型，结构体和类
	* 可以通过序列化来将浮点型，结构体和类转化成字符串，从而得到支持
*/

namespace game
{
	template<class K>
	class HashSet
	{
	public:
		HashSet(unsigned int size = 256)
			: m_size((size <= 0) ? 1 : size)
			, m_memory_pool(sizeof(KeyNode), m_size / 2)
		{
			m_hash_list = (KeyNode **)malloc(m_size * sizeof(KeyNode*));
			memset(m_hash_list, NULL, m_size * sizeof(KeyNode*));
		}

		virtual ~HashSet()
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
			KeyNode			*next;
		};

		bool		Push(K key, V &val);
		void		Erase(K key);

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

	protected:
		unsigned int	m_size;
		KeyNode			**m_hash_list;
		MemoryPool		m_memory_pool;
	};

	template<class K>
	bool game::HashSet<K>::Insert(K key)
	{
		unsigned int real_key = key % m_size;

		KeyNode *node = (KeyNode *)m_memory_pool.Alloc();
		node->key = key;

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


	template<class K>
	void game::HashSet<K>::Erase(K key)
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
}

#endif