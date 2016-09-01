
#include "field.h"
#include "lib/include/base/function.h"

bool Field::Write(rapidjson::Writer<rapidjson::StringBuffer> &writer)
{
	writer.StartObject();
	writer.Key(FIELD_VER_NAME);
	if (!writer.Int(ver))
	{
		Function::Error("can not write version");
		return false;
	}
	if (!Serialize(writer))
	{
		Function::Error("can not write field");
		return false;
	}
	return writer.EndObject();
}

bool Field::Read(DataUpdate &du, int len, char *str, bool update)
{
	rapidjson::Document doc; 
	if (doc.Parse(str).HasParseError())
	{
		Function::Error("string is not json");
		return false; 
	}
	if (!doc.IsObject())
	{
		Function::Error("data is not a json object");
		return false; 
	}

	if (!doc.HasMember(FIELD_VER_NAME) || !doc[FIELD_VER_NAME].IsInt())
	{
		Function::Error("can not read version");
		return false;
	}

	if (ver != (Version)doc[FIELD_VER_NAME].GetInt())
	{
		if (update)
		{
			char *new_str = du.OnUpdate(GetName(), len, str);
			if (new_str == NULL)
			{
				Function::Error("module %s can not update data", GetName());
				return false;
			}
			// todo 检测局部变量new_str再传指针，是否会报错
			return Read(du, 0, new_str, false);
		}
		Function::Error("data update fail");
		return false;
	}
		
	return Deserialize(doc, str);
}