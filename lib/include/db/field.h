
#ifndef TABLE_FIELD_H
#define TABLE_FIELD_H

#ifdef __unix
#define RAPIDJSON_ASSERT(X)
#endif

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
static inline bool	JsonWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer, const char *val){ return writer.String(val, strlen(val)); }

static inline bool	JsonRead(const rapidjson::Value &array, int index, int &val)
{if(index < (int)array.Size() && array[index].IsInt()){val = array[index].GetInt();return true;} return false;}

static inline bool	JsonRead(const rapidjson::Value &array, int index, unsigned int &val)
{if(index < (int)array.Size() && array[index].IsInt()){val = array[index].GetInt();return true;} return false;}

static inline bool	JsonRead(const rapidjson::Value &array, int index, unsigned long long &val)
{if(index < (int)array.Size() && array[index].IsInt()){val = array[index].GetInt();return true;} return false;}

static bool	JsonRead(const rapidjson::Value &array, int index, char *val, int len)
{
	if (index < (int)array.Size() && array[index].IsString()){
		int length = array[index].GetStringLength();
		length = length > len ? len : length; 
		memcpy(val, array[index].GetString(), length);
		return true;
	} 
	return false;
}

static const char *FIELD_BASE_NAME = "base";
static const char *FIELD_VER_NAME = "ver";

typedef unsigned short 	Version;
typedef unsigned char 	FieldIndex;

#define NewField(Class) \
	[]()->Field *{return new Class(); }

// todo 优化，继承的对象不再定义字段，整个模块的数据由外部传进入，这样方便通过memcpy将整个数据传到其它线程处理

class Field
{
public:
	Field(){}
	virtual ~Field(){}

	virtual const char *GetName() = 0;	// 获取字段名，用于构建sql
	virtual FieldIndex 	GetIndex() = 0;
	virtual bool 		IsBase(){return true;}
	//unsigned char 
};

// 基础类型继承Field，文本类型继承下面的TextField

// 只用于用json保存的数据

// class TextField : public Field
// {
// public:
// 	TextField() :Field(), ver(0){}
// 	virtual ~TextField(){}
// 
// 	bool 	IsBase(){return false;}
// 
// 	bool Write(rapidjson::Writer<rapidjson::StringBuffer> &writer);
// 	bool Read(int len, char *str, DataUpdate *du = NULL);
// 
// 	
// 	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> &writer) = 0;
// 	virtual bool Deserialize(rapidjson::Document &doc, char *str) = 0;
// 
// 	Version ver;
// 
// protected:
// };

// 严格的文本字段，不需要更新数据

class StrictTextField : public Field
{
public:
	StrictTextField() :Field(), ver(0){}
	virtual ~StrictTextField(){}

	bool Write(rapidjson::Writer<rapidjson::StringBuffer> &writer);
	bool Read(int len, char *str);


	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> &writer) = 0;
	virtual bool Deserialize(rapidjson::Document &doc, char *str) = 0;

	Version ver;

protected:
};

#endif