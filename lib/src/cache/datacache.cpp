
#include "datacache.h"

// void DataCache::FieldDefine( unsigned short name, unsigned short type, unsigned int length )
// {
// 	static DataField field;
// 	field.name		= name;
// 	field.type		= type;
// 	field.length	= length;
// 	m_fields.push_back(field);
// }

RowData::RowData(unsigned short length)
: m_data(length)
, m_field_length(length)
{
	m_data.Init(length);
}

bool RowData::Find(DataList &list)
{
	unsigned short field = 0;
	FieldData data;
	for (DATA_VECTOR::iterator itr = m_data.Begin(); itr != m_data.End(); ++itr, ++field)
	{
		data.field = false;
		data.value = *itr;
		list.Push(data);
	}
	return true;
}

bool RowData::Update(DataList &list)
{
	for (DataList::iterator itr = list.Begin(); itr != list.End(); ++itr)
	{
		if (itr->field >= m_field_length)
		{
			return false;
		}
		m_data[itr->field] = itr->value;
	}
	return true;
}
