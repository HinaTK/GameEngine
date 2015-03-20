
#ifndef DATA_MAP_H
#define	DATA_MAP_H

#include "libcommon/mutex.h"
#include "common/datastructure/gamemap.h"
#include "common/datastructure/gamelist.h"
#include "database.h"

/*
	一个集合，用一个DataMap，因为Key需要唯一
*/
template<class T>
class DataMap : public CacheBase
{
public:
	DataMap();
	~DataMap();

	struct DataInfo
	{
		const char		*data;
		unsigned int	length;
	};

	struct DirtyData
	{
		int type;
		T	key;
		DataInfo	info;
	};

	typedef game::Map<T, DataInfo>	DATA_MAP;
	typedef game::List<DirtyData>	DIRTY_DATA_LIST;

	void		SetCallBack(DataCallBack *callback){ m_data_call_back = callback; }
	bool		Insert(T &key, const char *data, unsigned int length);
	bool		Update(T &key, const char *data, unsigned int length);
	bool		UpdateAndInsert(T &key, const char *data, unsigned int length);
	bool		Find(T &key);
	bool		Find(T &key, const char **data, unsigned int &length);
	bool		Delete(T &key);

	void		Flush();		// 冲刷脏数据

private:
	DataCallBack			*m_data_call_back;
	DATA_MAP				m_data_map;
	DIRTY_DATA_LIST			m_dirty_data_list;
	Mutex					m_mutex;
};

template<class T>
DataMap<T>::DataMap()
: m_data_call_back(NULL)
{

}

template<class T>
DataMap<T>::~DataMap()
{

}
template<class T>
bool DataMap<T>::Insert(T &key, const char *data, unsigned int length)
{
	DirtyData dd;
	dd.type = DB_INSERT;
	dd.key = key;
	dd.info.data = data;
	dd.info.length = length;
	m_data_map.Insert(key, dd.info);
	MutexLock lock(&m_mutex);
	m_dirty_data_list.PushBack(dd);
	return true;
}

template<class T>
bool DataMap<T>::Update(T &key, const char *data, unsigned int length)
{
	game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		return false;
	}
	itr->second.data = data;
	itr->second.length = length;

	DirtyData dd;
	dd.type = DB_UPDATE;
	dd.key = key;
	dd.info.data = data;
	dd.info.length = length;
	MutexLock lock(&m_mutex);
	m_dirty_data_list.PushBack(dd);
	return true;
}

template<class T>
bool DataMap<T>::UpdateAndInsert(T &key, const char *data, unsigned int length)
{
	if (!Update(key, data, length))
	{
		return Insert(key, data, length);
	}
}

template<class T>
bool DataMap<T>::Find(T &key)
{
	game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		return false;
	}

	m_data_call_back->OnCallBack((char *)&key, DB_FIND, itr->second.data, itr->second.length);
	return true;
}

template<class T>
bool DataMap<T>::Find(T &key, const char **data, unsigned int &length)
{
	game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		return false;
	}
	*data = itr->second.data;
	length = itr->second.length;
	return true;
}

template<class T>
bool DataMap<T>::Delete(T &key)
{
	game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		return false;
	}

	DirtyData dd;
	dd.type = DB_DELETE;
	dd.key = key;
	dd.info.data = itr->second.data;
	dd.info.length = itr->second.length;
	MutexLock lock(&m_mutex);
	m_dirty_data_list.PushBack(dd);
}


template<class T>
void DataMap<T>::Flush()
{
	MutexLock lock(&m_mutex);
	for (DIRTY_DATA_LIST::iterator itr = m_dirty_data_list.Begin(); itr != m_dirty_data_list.End(); ++itr)
	{
		m_data_call_back->OnCallBack((char *)&itr->key, itr->type, itr->info.data, itr->info.length);
	}
	m_dirty_data_list.Clear();
}

#endif