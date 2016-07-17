
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
static const char *FIELD_VER_NAME = "ver";

typedef unsigned short Version;

class Field
{
public:
	Field(Version _ver) :m_dirty(false), ver(_ver){}
	virtual ~Field(){}

	void	SetDirty(){ m_dirty = true; }
	void	UnsetDirty(){ m_dirty = false; }

	inline bool Error(int err){ m_err = err; return false; }
	inline bool Error(int err, int line){ m_err = err; m_err_line = line;  return false; }

	bool inline WriteVer(rapidjson::Writer<rapidjson::StringBuffer> &writer)
	{
		writer.Key(FIELD_VER_NAME);
		return writer.Int(ver);
	}

	bool ReadVer(rapidjson::Document &doc)
	{
		if (doc.HasMember(FIELD_VER_NAME) && doc[FIELD_VER_NAME].IsInt())
		{
			ver = (Version)doc[FIELD_VER_NAME].GetInt();
			return true;
		}
		m_err = ERR_NO_THIS_FIELD;
		return false;
	}

	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> &writer, std::string &str) = 0;

	Version ver;

protected:
	bool	m_dirty;
	int m_err;
	int m_err_line;
};

#endif