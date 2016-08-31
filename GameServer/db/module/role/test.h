
#ifndef MODULE_TEST_H
#define MODULE_TEST_H

#include "lib/include/db/field.h"

class MTest : public Field
{
public:
	MTest():Field(){ver = 2;}
	~MTest(){}

	char *GetName(){ return "test"; }
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer> &writer)
	{
		JSON_WRITE_BASE_ARRAY_BEGIN(writer, FIELD_BASE_NAME);
		writer.Int(item_id);
		JSON_WRITE_BASE_ARRAY_END(writer);
		return true;
	}

	virtual bool Deserialize(rapidjson::Document &doc, char *str)
	{
		JSON_READ_BASE_ARRAY_BEGIN(FIELD_BASE_NAME);
		JSON_READ_ARRAY_INT(array, 0, item_id);
		JSON_READ_BASE_ARRAY_END();
		return true;
	}

	int item_id;
};

#endif
