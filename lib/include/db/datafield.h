
#ifndef DATA_FIELD_H
#define DATA_FIELD_H

#include <vector>
#include "field.h"
#include "common/serverdef.h"

class DataField
{
public:
	~DataField()
	{
		for (std::vector<Field *>::iterator itr1 = keys.begin(); itr1 != keys.end(); ++itr1)
		{
			delete *itr1;
		}

		for (std::vector<Field *>::iterator itr2 = fields.begin(); itr2 != fields.end(); ++itr2)
		{
			delete *itr2;
		}
	}

	void SetKey(Field *key){keys.push_back(key);}
	void SetField(Field *field){fields.push_back(field);}

private:	
	std::vector<Field *> keys;
	std::vector<Field *> fields;
};


#endif