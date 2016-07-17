
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
typedef unsigned short Version;

template<class DATA> 
class Field
{
public:
	Field(const char *name, Version ver = 0)
		: m_name(name)
		, m_ver(ver)
		, m_err(0)
		, m_err_line(0){}
	~Field(){};

	

	inline bool Error(int err){ m_err = err; return false; }
	inline bool Error(int err, int line){ m_err = err; m_err_line = line;  return false; }

	bool inline WriteVer(rapidjson::Writer<rapidjson::StringBuffer> &writer, DATA &data)
	{
		writer.Key("ver");
		return writer.Int(data.ver);
	}

	bool ReadVer(rapidjson::Document &doc, Version &ver)
	{
		if (doc.HasMember("ver") && doc["ver"].IsInt())
		{
			ver = (Version)doc["ver"].GetInt();
		}
		m_err = ERR_NO_THIS_FIELD;
		return false;
	}

	virtual void Serialize(DATA &data, rapidjson::Writer<rapidjson::StringBuffer> &writer) = 0;
	virtual bool Deserialize(rapidjson::StringBuffer::Ch *str, DATA &data) = 0;
protected:
	Version m_ver;
	std::string m_name;

	int m_err;
	int m_err_line;
};

class Model
{
public:
	Model(Version _ver) :m_dirty(false), ver(_ver){}
	virtual ~Model(){}

	void	SetDirty(){ m_dirty = true; }
	void	UnsetDirty(){ m_dirty = false; }

	Version ver;

protected:
	bool	m_dirty;
};

#endif