
#ifndef SORT_MAP_H
#define SORT_MAP_H

#include "gamemap.h"
#include "gamevector.h"
#include "lib/include/common/memorypool.h"

/*
	有序映射，具快速插入、查找及排序的能力
	游戏中的应用：活动、副本等实时积分排名
*/

namespace game
{
template<class K, class V>
class SortMap
{
public:
	SortMap(unsigned int size = 64)
		: m_index(size)
		, m_data(size)
		, m_memory_pool(sizeof(RankData), size)
	{}
	~SortMap(){};

	class RankData
	{
	public:
		unsigned int rank;
		K first;
		V second;
	};

private:
	typedef Map<K, RankData* >	INDEX_MAP;
	typedef Vector<RankData* >	RANK_DATA;

public:
	template<class T, class Handle = SortMap>
	class Iterator
	{
		friend class SortMap;
	public:
		Iterator() :m_index(0){}
		Iterator(unsigned int index, Handle *hadle = 0) :m_index(index), m_handle(hadle){}
		~Iterator(){}

		Iterator<T, Handle>& operator ++()
		{
			++m_index;
			return *this;
		}

		Iterator<T, Handle>& operator --()
		{
			--m_index;
			return *this;
		}

		RankData* operator->() { return m_handle->m_data[m_index]; }
		RankData& operator*() { return *m_handle->m_data[m_index]; }

		bool operator==(const Iterator<T, Handle> &right) const { return (m_index == right.m_index && m_handle == right.m_handle); }
		bool operator!=(const Iterator<T, Handle> &right) const { return (m_index != right.m_index || m_handle != right.m_handle); }

		unsigned m_index;
	private:
		Handle *m_handle;
	};

	typedef Iterator<V> iterator;

	unsigned int	Insert(K &key, V &data);

	iterator		Find(K &key)
	{
		typename INDEX_MAP::iterator itr = m_index.Find(key);
		if (itr == m_index)
		{
			return End();
		}
		return iterator(itr->second->rank - 1, this);
	}

	iterator		Begin(){ return iterator(0, this); }

	iterator		End(){ return iterator(m_data.Size(), this); }


private:
	INDEX_MAP m_index;
	RANK_DATA m_data;
	MemoryPool m_memory_pool;
};

template<class K, class V>
unsigned int SortMap<K, V>::Insert(K &key, V &data)
{
	typename INDEX_MAP::iterator itr = m_index.Find(key);
	if (itr == m_index.End())
	{
		RankData *rank_data = (RankData *)m_memory_pool.Alloc();
		rank_data->first = key;
		rank_data->second = data;
		m_data.Push(rank_data);
		rank_data->rank = m_data.Size();
		m_index.Insert(key, rank_data);
		itr = m_index.Find(key);
	}

	if (itr->second->rank < 1)
	{
		return 0;
	}
	itr->second->second = data;
	unsigned int new_rank = itr->second->rank;
	RankData *temp_data;
	// 向上冒泡
	for (int i = (int)(itr->second->rank - 1); i > 0; --i)
	{
		if (m_data[i]->second <= m_data[i - 1]->second)
		{
			break;
		}
		temp_data = m_data[i - 1];
		m_data[i - 1] = m_data[i];
		m_data[i] = temp_data;
		m_data[i]->rank = i + 1;
		--new_rank;
	}

	// 向下冒泡
	for (int i = (int)itr->second->rank; i < (int)m_data.Size(); ++i)
	{
		// 结构体传入的时候需要重载
		if (m_data[i - 1]->second >= m_data[i]->second)
		{
			break;
		}
		temp_data = m_data[i - 1];
		m_data[i - 1] = m_data[i];
		m_data[i] = temp_data;
		m_data[i - 1]->rank = i;
		++new_rank;
	}
	itr->second->rank = new_rank;
	return itr->second->rank;
}

}
#endif