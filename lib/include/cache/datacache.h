#ifndef DATACACHE_H
#define DATACACHE_H

#include <list>
#include "dataadapter.h"
#include "common/datastructure/gamehash.h"

// static DataField field;
// #define FIELD_DEFINE(Obj, Name, Type, Length)\
// 	field.name = Name;\
// 	field.type = Type;\
// 	field.length = Length;\
// 	Obj.##m_fields.push_back(field);\


class DataCache
{
public:
	typedef std::vector<DataField> DATAFIELD_VECTOR;
	typedef std::vector<DataValue> DATAVALUE_VECTOR;

public:
	DataCache(unsigned int hash_size = 256, unsigned int data_size = 1024)
		//: m_data(hash_size)
	{
		
	}
	~DataCache(){};

	struct OperTime
	{
		unsigned int index;
		unsigned int time;
	};
	
	void	FieldDefine(unsigned short name, unsigned short type, unsigned int length);

public:
	DATAFIELD_VECTOR							m_fields;			// 数据表的定义
	//DATAVALUE_HASH								m_data;				// 该表的所有cache数据
	std::vector<unsigned int>					m_dirty_data;		// 脏数据，用于持久化
	std::list<OperTime>							m_oper_time;		// 数据的操作时间，用于LRU
	
};

// class DataCacheStr
// {
// public:
// 	typedef std::vector<DataField> DATAFIELD_VECTOR;
// 	typedef std::vector<DataValue> DATAVALUE_VECTOR;
// 	typedef StrHashList<DATAVALUE_VECTOR> DATAVALUE_HASH;
// 
// public:
// 	DataCacheStr(unsigned int hash_size = 256, unsigned int data_size = 1024)
// 		: m_data(hash_size)
// 	{
// 		
// 	}
// 	~DataCacheStr(){};
// 
// 	void	FieldDefine(unsigned char name, unsigned char type, unsigned short length);
// 
// 	DATAFIELD_VECTOR							m_fields;			// 数据表的定义
// 	DATAVALUE_HASH								m_data;				// 该表的所有cache数据
// 	std::vector<unsigned int>					m_dirty_data;		// 脏数据，用于持久化
// public:
// 
// };

#endif