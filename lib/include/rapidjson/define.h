

#ifndef RAPIDJSON_DEFINE_H
#define RAPIDJSON_DEFINE_H

#include "document.h"
#include "prettywriter.h"
#include "stringbuffer.h"

enum
{
	ERR_IS_NOT_JSON = 1,	// 不是Json
	ERR_IS_NOT_OBJECT,		// 不是对象
	ERR_DATA_TYPE_ERR,		// 数据类型不对
	ERR_READ_DATA_ERR,		// 数据读取错误
	ERR_NO_THIS_FIELD		// 没有这个字段
};

#define JSON_BASIC_CHECK(Str)\
	rapidjson::Document doc; \
	if (doc.Parse(Str).HasParseError())\
	{\
		return Error(ERR_IS_NOT_JSON); \
	}\
	if (!doc.IsObject())\
	{\
		return Error(ERR_IS_NOT_OBJECT); \
	}

#define JSON_WRITE_BASE_ARRAY_BEGIN(Name)\
	m_writer.Key(Name); \
	m_writer.StartArray();

#define JSON_WRITE_BASE_ARRAY_END()\
	m_writer.EndArray();

#define JSON_READ_BASE_ARRAY_BEGIN(Name)\
	if (doc.HasMember(Name) && doc[Name].IsArray()){ \
		rapidjson::Value &array = doc[Name]; \
		unsigned int size = array.Size();

#define JSON_READ_BASE_ARRAY_END() \
	}\
	else return Error(ERR_NO_THIS_FIELD, __LINE__);

#define JSON_READ_ONE_ARRAY_BEGIN(Name)\
	if (doc.HasMember(Name) && doc[Name].IsArray()){\
		rapidjson::Value &array = doc[Name]; \
		for (unsigned int i = 0; i < array.Size(); ++i)\
		{\
			const Value& sub = array[i];

#define JSON_READ_ONE_ARRAY_END() \
		}\
	}\
	else return Error(ERR_NO_THIS_FIELD, __LINE__);

#define JSON_READ_ARRAY_INT(Array, Index, Val) \
	if (size > Index && Array[Index].IsInt())\
	{\
		Val = Array[Index].GetInt(); \
	}\
	else return Error(ERR_READ_DATA_ERR, __LINE__);


// 以下一一对应
#define JSON_WRITE_TWO_ARRAY_BEGIN(Name, Vector, Itr)\
	m_writer.Key(Name);\
	m_writer.StartArray();\
	for (Itr itr = Vector.begin(); itr != Vector.end(); ++itr)\
	{\
		m_writer.StartArray();
	
#define JSON_WRITE_TWO_ARRAY_END() \
		m_writer.EndArray();\
	}\
	m_writer.EndArray();

#define JSON_READ_TWO_ARRAY_BEGIN(Name)\
	if (doc.HasMember(Name) && doc[Name].IsArray()){\
	Value &array = doc[Name]; \
	for (unsigned int i = 0; i < array.Size(); ++i)\
	{\
		const Value& sub = array[i]; \
		if (!sub.IsArray())\
		{\
			return Error(ERR_IS_NOT_OBJECT, __LINE__); \
		}\
		unsigned int size = sub.Size(); \

#define JSON_READ_TWO_ARRAY_END() \
		}\
	}

#define JSON_WRITE_ARRAY_INT_SET(Name, Set)\
	m_writer.Key(Name); \
	m_writer.StartArray(); \
	for (std::set<int>::iterator itr = Set.begin(); itr != Set.end(); ++itr)\
	{\
		JsonWrite(m_writer, *itr); \
	}\
	m_writer.EndArray();


#define JSON_READ_ARRAY_INT_SET(Name, Set) \
	JSON_READ_ONE_ARRAY_BEGIN(Name); \
	if (sub.IsInt())\
	{\
		Set.insert(sub.GetInt()); \
	}\
	else return Error(ERR_READ_DATA_ERR, __LINE__);\
	JSON_READ_ONE_ARRAY_END();



#endif