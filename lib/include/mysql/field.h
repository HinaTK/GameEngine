
#ifndef TABLE_FIELD_H
#define TABLE_FIELD_H

#include <string>
#include <stdint.h>
#include "lib/include/rapidjson/document.h"
#include "lib/include/rapidjson/prettywriter.h"
#include "lib/include/rapidjson/stringbuffer.h"

static inline bool	JsonWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer, bool val){ return writer.Bool(val); }
static inline bool	JsonWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer, int val){ return writer.Int(val); }
static inline bool	JsonWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer, unsigned int val){ return writer.Uint(val); }
static inline bool	JsonWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer, int64_t val){ return writer.Int64(val); }
static inline bool	JsonWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer, uint64_t val){ return writer.Uint64(val); }
static inline bool	JsonWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer, double val){ return writer.Double(val); }

template<class DATA> 
class Field
{
public:
	Field(const char *name, int ver = 0)
		: m_name(name), m_ver(ver), m_writer(m_s), m_err(0){}
	~Field(){};

	enum
	{
		ERR_IS_NOT_JSON = 1,	// 不是Json
		ERR_IS_NOT_OBJECT,		// 不是对象
		ERR_DATA_TYPE_ERR		// 数据类型不对
	};

	inline bool Error(int err){ m_err = err; return false; }

	bool Init()
	{
		m_writer.StartObject();
		m_writer.Key("ver");
		m_writer.Int(m_ver);
		m_writer.Key("base");
		return m_writer.StartArray();
	}

	bool DeInit()
	{
		return true;
	}

	bool ReadVector()
	{
		return true;
	}

	bool CheckArray()
	{
		return true;
	}

	virtual void Serialize(DATA &data) = 0;
	virtual bool Deserialize(rapidjson::StringBuffer::Ch *str, DATA &data) = 0;
protected:
	int m_ver;
	std::string m_name;

	rapidjson::StringBuffer m_s;
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;

	int m_err;
};

#endif