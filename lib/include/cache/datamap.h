
#ifndef DATA_MAP_H
#define	DATA_MAP_H

#include <mutex>
#include "common/datastructure/gamemap.h"
#include "common/datastructure/gamelist.h"

/*
version:20150504
data(数据)空间由外部申请, 设置回调进行释放
*/
class DataCallBack
{
public:
	DataCallBack(){}
	~DataCallBack(){}

	virtual void OnCallBack(unsigned char *key, int operater, const char *data, unsigned int length) = 0;

	virtual void OnDelete(const char *data){ delete data; }
};

/*
	* 一个集合，用一个DataMap，因为Key需要唯一
	* 当key是字符串，请使用使用std::string表示
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
	typedef game::List<const char *>		DELETE_DATA_LIST;

	void		SetCallBack(DataCallBack *callback){ m_data_call_back = callback; }
	bool		Insert(T &key, const char *data, unsigned int length);
	bool		Update(T &key, const char *data, unsigned int length);
	bool		UpdateOrInsert(T &key, const char *data, unsigned int length);
	bool		Find(T &key);
	bool		Find(T &key, const char **data, unsigned int &length);
	bool		Delete(T &key);

	void		Flush();		// 冲刷脏数据

	// 事务
	void		Begin(){ m_is_transaction = true; }
	void		RollBack();
	void		Commit();
private:
	DataCallBack			*m_data_call_back;
	DATA_MAP				m_data_map;
	DIRTY_DATA_LIST			*m_dirty_data_list;
	DIRTY_DATA_LIST			*m_flush_list;
	DIRTY_DATA_LIST			m_transaction_list;		// 事务临时数据列表
	DELETE_DATA_LIST		m_delete_data_list;
	std::mutex				m_mutex;
	bool					m_is_transaction;
};

#define MUTEX_LOCK()\
	m_mutex.lock(); \
{

#define MUTEX_UNLOCK()\
}\
	m_mutex.unlock();

template<class T>
DataMap<T>::DataMap()
: m_data_call_back(NULL)
, m_is_transaction(false)
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

	if (m_is_transaction)
	{
		m_transaction_list.PushBack(dd);
	}
	else
	{
		m_data_map.Insert(key, dd.info);
		MUTEX_LOCK();
		m_dirty_data_list->PushBack(dd);
		MUTEX_UNLOCK();
	}

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

	DirtyData dd;
	dd.type = DB_UPDATE;
	dd.key = key;
	dd.info.data = data;
	dd.info.length = length;

	if (m_is_transaction)
	{
		m_transaction_list.PushBack(dd);
	}
	else
	{
		m_delete_data_list.PushBack(itr->second.data);

		itr->second.data = data;
		itr->second.length = length;

		MUTEX_LOCK();
		m_dirty_data_list->PushBack(dd);
		MUTEX_UNLOCK();
	}
	return true;
}

template<class T>
bool DataMap<T>::UpdateOrInsert(T &key, const char *data, unsigned int length)
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

	m_data_call_back->OnCallBack((unsigned char *)&key, DB_FIND, itr->second.data, itr->second.length);
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

	if (m_is_transaction)
	{
		m_transaction_list.PushBack(dd);
	}
	else
	{
		MUTEX_LOCK();
		m_dirty_data_list->PushBack(dd);
		MUTEX_UNLOCK();

		m_delete_data_list.PushBack(itr->second.data);
		m_data_map.Erase(itr->first);
	}
	return true;
}

// 这里不对OnCallBack统一加锁，需要加锁时，到指定函数进行加锁
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
		m_data_call_back->OnCallBack((unsigned char *)&itr->key, itr->type, itr->info.data, itr->info.length);
	}
	m_flush_list->Clear();

	for (typename DELETE_DATA_LIST::iterator itr = m_delete_data_list.Begin(); itr != m_delete_data_list.End(); ++itr)
	{
		m_data_call_back->OnDelete(itr->second.data);
	}
	m_delete_data_list.Clear();
}


template<class T>
void DataMap<T>::RollBack()
{
	m_is_transaction = false;
	m_transaction_list.Clear();
}


template<class T>
void DataMap<T>::Commit()
{
	m_is_transaction = false;
	for (typename DIRTY_DATA_LIST::iterator itr = m_transaction_list.Begin(); itr != m_transaction_list.End(); ++itr)
	{
		switch (itr->type)
		{
		case DB_INSERT:
			Insert(itr->key, itr->info.data, itr->info.length);
			break;
		case DB_UPDATE:
			Update(itr->key, itr->info.data, itr->info.length);
			break;
		case DB_DELETE:
			Delete(itr->key);
			break;
		}
	}
	m_transaction_list.Clear();
}

#endif