
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

static const char *FIELD_BASE_NAME = "base";

template<class DATA> 
class Field
{
public:
	Field(const char *name, int ver = 0)
		: m_name(name)
		, m_ver(ver)
		, m_writer(m_s)
		, m_err(0)
		, m_err_line(0){}
	~Field(){};

	

	inline bool Error(int err){ m_err = err; return false; }
	inline bool Error(int err, int line){ m_err = err; m_err_line = line;  return false; }

	bool Init()
	{
		m_writer.StartObject();
		m_writer.Key("ver");
		return m_writer.Int(m_ver);
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
	int m_err_line;
};

#endif