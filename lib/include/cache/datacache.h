#ifndef DATACACHE_H
#define DATACACHE_H

#include <list>
#include "dataadapter.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamemap.h"
#include "lib/include/common/memorypool.h"

typedef game::Vector<FieldData> DataList;

class RowData
{
	typedef game::Vector<DataValue> DATA_VECTOR;
public:
	RowData(unsigned short length);
	~RowData(){}

	bool	Find(DataList &list);

	bool	Update(DataList &list);

	DATA_VECTOR &GetDate(){ return m_data; }

private:
	DATA_VECTOR	m_data;
	unsigned short m_field_length;
};

/*
	考虑加上事务处理
*/

template <class K>
class DataCache
{
public:
	typedef game::Vector<FieldInfo> DATAFIELD_VECTOR;	
	typedef game::Map<K, RowData *>	DATA_MAP;

public:
	DataCache(unsigned short length)
		: m_data_map(128)
		, m_field_length(length)
	{
		
	}
	~DataCache(){};

	struct OperTime
	{
		unsigned int index;
		unsigned int time;
	};
	
	void	FieldDefine(unsigned short name, unsigned short type, unsigned int length);

	bool	Find(K &key, DataList &list);

	bool	Update(K &key, DataList &list, bool insert = true);

public:
	DATAFIELD_VECTOR						m_fields;			// 数据表的定义
	
private:
	DATA_MAP								m_data_map;
	unsigned short m_field_length;
};

template <class K>
void DataCache<K>::FieldDefine(unsigned short name, unsigned short type, unsigned int length)
{
	static FieldInfo field;
	field.name = name;
	field.type = type;
	field.length = length;
	m_fields.Push(field);
}

template <class K>
bool DataCache<K>::Find(K &key, DataList &list)
{
	DATA_MAP::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		return false;
	}
	return itr->second->Find(list);
}

template <class K>
bool DataCache<K>::Update(K &key, DataList &list, bool insert /*= true*/)
{
	DATA_MAP::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		if (insert)
		{
			RowData *data = new RowData(m_field_length);
			data->Update(list);
			m_data_map.Insert(key, data);
			return true;
		}
		return false;
	}

	return itr->second->Update(list);
}


#endif