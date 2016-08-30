
#ifndef TABLE_FIELD_H
#define TABLE_FIELD_H

#include <string>
#include <stdint.h>
#include "dataupdate.h"
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

// 只用于用json保存的数据

class Field
{
public:
	Field() :m_dirty(false), ver(0){}
	virtual ~Field(){}

	bool 	IsDirty(){return m_dirty;}
	void	SetDirty(){ if (!m_dirty) m_dirty = true; }
	void	UnsetDirty(){ m_dirty = false; }

	bool Write(rapidjson::Writer<rapidjson::StringBuffer> &writer);
	bool Read(DataUpdate &du, int len, char *str, bool update = true);

	virtual char *	GetName() = 0;	// 获取字段名，用于构建sql
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> &writer) = 0;
	virtual bool Deserialize(rapidjson::Document &doc, char *str) = 0;

	Version ver;

protected:
	bool	m_dirty;
};

#endif