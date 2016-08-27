
#ifndef MODULE_TEST_H
#define MODULE_TEST_H

#include "lib/include/db/field.h"

class MTest : public Field
{
public:
	MTest():Field(){ver = 1;}
	~MTest(){}

	char *GetName(){ return "test"; }
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> &writer)
	{
		JSON_WRITE_BASE_ARRAY_BEGIN(writer, FIELD_BASE_NAME);
		writer.Int(112234);
		JSON_WRITE_BASE_ARRAY_END(writer);
		return true;
	}

	virtual bool Deserialize(char *str)
	{
		return true;
	}

	int item_id;
};

#endif
