
#ifndef DATA_MAP_H
#define	DATA_MAP_H

#include "lib/include/common/mutex.h"
#include "common/datastructure/gamemap.h"
#include "common/datastructure/gamelist.h"

// version:20150430

class DataCallBack
{
public:
	DataCallBack(){}
	~DataCallBack(){}

	virtual void OnCallBack(char *key, int operater, const char *data, unsigned int length) = 0;
};

/*
	一个集合，用一个DataMap，因为Key需要唯一
*/
template<class T>
class DataMap
{
public:
	DataMap();
	~DataMap();

	enum
	{
		INVALID,
		DB_INSERT,
		DB_DELETE,
		DB_FIND,
		DB_UPDATE
	};

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
	DIRTY_DATA_LIST			*m_dirty_data_list;
	DIRTY_DATA_LIST			*m_flush_list;
	Mutex					m_mutex;
};

template<class T>
DataMap<T>::DataMap()
: m_data_call_back(NULL)
{
	m_dirty_data_list = new DIRTY_DATA_LIST;
	m_flush_list = new DIRTY_DATA_LIST;
}

template<class T>
DataMap<T>::~DataMap()
{
	if (m_data_call_back != NULL)
	{
		delete m_data_call_back;
	}

	delete m_dirty_data_list;
	delete m_flush_list;
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
	m_dirty_data_list->PushBack(dd);
	return true;
}

template<class T>
bool DataMap<T>::Update(T &key, const char *data, unsigned int length)
{
	typename game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
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
	m_dirty_data_list->PushBack(dd);
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
	typename game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
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
	typename game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
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
	typename game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
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
	m_dirty_data_list->PushBack(dd);
}


template<class T>
void DataMap<T>::Flush()
{
	{
		MutexLock lock(&m_mutex);
		DIRTY_DATA_LIST *temp = m_dirty_data_list;
		m_dirty_data_list = m_flush_list;
		m_flush_list = temp;
	}
	for (typename DIRTY_DATA_LIST::iterator itr = m_flush_list->Begin(); itr != m_flush_list->End(); ++itr)
	{
		m_data_call_back->OnCallBack((char *)&itr->key, itr->type, itr->info.data, itr->info.length);
	}
	m_flush_list->Clear();
}

#endif