#ifndef DATACACHE_H
#define DATACACHE_H

#include "dataadapter.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamemap.h"
#include "common/datastructure/gamelist.h"
#include "lib/include/common/mutex.h"

typedef game::Vector<FieldData> DataList;
typedef game::Vector<DataValue> DataVector;

class CallBack
{
public:
	CallBack(){}
	~CallBack(){}

	virtual void OnCallBack(char *key, int operater, DataVector &vector) = 0;
};


class RowData
{
public:
	RowData(unsigned short length);
	~RowData(){}

	bool	Find(DataList &list);

	bool	Update(DataList &list);

	DataVector &GetData(){ return m_data; }

	void *		operator new(size_t c);
	void		operator delete(void *m);

private:
	DataVector		m_data;
	unsigned short	m_field_length;
};

/*
	考虑加上事务处理
	* 设置该表的的事务状态(begin)
	* 将期间操作的数据的操作类型，Key及DataList保存起来
	* 直到commit或discard再操作保存起来的数据
*/

template <class K>
class DataCache
{
public:
	typedef game::Vector<FieldInfo> DATAFIELD_VECTOR;	
	typedef game::Map<K, RowData *>	DATA_MAP;
	//typedef typename DATA_MAP::iterator iterator;

public:
	DataCache(unsigned short length)
		: m_data_map(128)
		, m_call_back(NULL)
		, m_dirty_data_list(NULL)
		, m_field_length(length)
	{
		
	}
	~DataCache(){};
	
	struct DirtyData
	{
		int		oper;
		K		key;
		RowData *row_data;
	};
	typedef game::List<DirtyData>	DirtyDataList;
	

	enum
	{
		DC_INVALID,
		DC_INSERT,
		DC_DELETE,
		DC_FIND,
		DC_UPDATE
	};

	void			FieldDefine(unsigned short name, unsigned short type, unsigned int length);
	void			SetCallBack(CallBack *call_back){ m_call_back = call_back; }
	void			SetDirtyList(DirtyDataList *list){ m_dirty_data_list = list; }
	DirtyDataList  *GetDirtyList(){ return m_dirty_data_list; }
	Mutex		   &GetMutex(){ return m_dirty_mutex; };

	bool			Find(K &key, DataList &list);

	bool			Update(K &key, DataList &list, bool insert = true);

	bool			Delete(K &key);

protected:
	void	SetDirtyData(int oper, K &key, RowData *row_data);

public:
	DATAFIELD_VECTOR	m_fields;			// 数据表的定义
	
private:
	DATA_MAP			m_data_map;
	DirtyDataList		*m_dirty_data_list;
	CallBack			*m_call_back;
	unsigned short		m_field_length;

	Mutex				m_dirty_mutex;
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
void DataCache<K>::SetDirtyData(int oper, K &key, RowData *row_data)
{
	DirtyData dd;
	dd.oper = oper;
	dd.key = key;
	dd.row_data = row_data;
	m_dirty_data_list->PushBack(dd);
}

template <class K>
bool DataCache<K>::Find(K &key, DataList &list)
{
	typename DATA_MAP::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		return false;
	}
	return itr->second->Find(list);
}

template <class K>
bool DataCache<K>::Update(K &key, DataList &list, bool insert /*= true*/)
{
	typename DATA_MAP::iterator itr = m_data_map.Find(key);
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

	if (itr->second->Update(list))
	{
		SetDirtyData(DC_UPDATE, key, itr->second);
		return true;
	}
	return false;
}

template <class K>
bool DataCache<K>::Delete(K &key)
{
	typename DATA_MAP::iterator itr = m_data_map.Erase(key);
	if (itr == m_data_map.End())
	{
		return false;
	}
	SetDirtyData(DC_DELETE, key, itr->second);
	return true;
}

#endif