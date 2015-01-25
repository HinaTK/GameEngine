
#include "datacache.h"

void DataCache::FieldDefine( unsigned short name, unsigned short type, unsigned int length )
{
	static DataField field;
	field.name		= name;
	field.type		= type;
	field.length	= length;
	m_fields.push_back(field);
}
