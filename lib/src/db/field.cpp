
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

static bool Check(rapidjson::Document &doc, char *str)
{
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
	return true;
}

bool Field::Read(DataUpdate &du, int len, char *str)
{
	rapidjson::Document doc; 
	if (!Check(doc, str))
	{
		return false;
	}

	if (ver != (Version)doc[FIELD_VER_NAME].GetInt())
	{
		char *new_str = du.OnUpdate(GetName(), len, str);
		if (new_str == NULL)
		{
			Function::Error("module %s can not update data", GetName());
			return false;
		}
		if (!Check(doc, new_str))
		{
			Function::Error("module %s data update fail", GetName());
			return false;
		}
		SetDirty();
		bool ret = Deserialize(doc, new_str);
		du.Release();
		return ret;
	}
		
	return Deserialize(doc, str);
}