
#ifndef DATA_MAP_H
#define	DATA_MAP_H

#include "common/datastructure/gamemap.h"
#include "database.h"

template<class T>
class DataMap : public DataBase
{
public:
	DataMap();
	~DataMap();

	bool		Insert(T &key, const char *data, unsigned int length, CallBackFunc func = NULL);
	bool		Update(T &key, const char *data, unsigned int length);
	bool		UpdateAndInsert(T &key, const char *data, unsigned int length, CallBackFunc func = NULL);
	bool		Find(T &key);
	bool		Find(T &key, const char **data, unsigned int &length);
	bool		Delete(T &key);


private:
	game::Map<T, DataInfo> m_data_map;
};

template<class T>
DataMap<T>::DataMap()
{

}

template<class T>
DataMap<T>::~DataMap()
{

}
template<class T>
bool DataMap<T>::Insert(T &key, const char *data, unsigned int length, CallBackFunc func /*= NULL*/)
{
	DataInfo info;
	info.data = data;
	info.length = length;
	info.func = func;
	m_data_map.Insert(key, info);
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
	return true;
}

template<class T>
bool DataMap<T>::UpdateAndInsert(T &key, const char *data, unsigned int length, CallBackFunc func /*= NULL*/)
{
	game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		return Insert(key, data, length, func);
	}
	itr->second.data = data;
	itr->second.length = length;
	return true;
}

template<class T>
bool DataMap<T>::Find(T &key)
{
	game::Map<T, DataInfo>::iterator itr = m_data_map.Find(key);
	if (itr == m_data_map.End())
	{
		return false;
	}
	itr->second.func(itr->second.data, itr->second.length);
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


#endif