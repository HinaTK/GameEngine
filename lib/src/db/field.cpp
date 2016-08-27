
#include "field.h"
#include "lib/include/base/function.h"

bool Field::Write(rapidjson::Writer<rapidjson::StringBuffer> &writer)
{
	writer.Key(FIELD_VER_NAME);
	if (!writer.Int(ver))
	{
		Function::Error("can not write version");
		return false;
	}
	return Serialize(writer);
}

bool Field::Read(char *str)
{
	rapidjson::Document doc; 
	if (doc.Parse(str).HasParseError())
	{
		Function::Error("string is not json");
		return false; 
	}
	if (!doc.IsObject())
	{
		Function::Error("json is not object");
		return false; 
	}

	if (!doc.HasMember(FIELD_VER_NAME) || !doc[FIELD_VER_NAME].IsInt())
	{
		Function::Error("can not read version");
		return false;
	}

	if (ver != (Version)doc[FIELD_VER_NAME].GetInt())
	{
		// todo 用lua作数据升级，减少包的大小
	}
		
	return Deserialize(str);
}