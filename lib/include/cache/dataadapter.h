
#ifndef DATAADAPTER_H
#define DATAADAPTER_H

//#include <vector>

enum DataType
{
	DT_CHAR,
	DT_INT,
	DT_LONG,		// 64位整型
	DT_FLOAT,
	DT_DOUBLE,
	DT_STR,		// 字符串
	DT_TIME
};

struct FieldInfo
{
	unsigned short	name;
	unsigned short	type;
	unsigned int	length;

};

union DataValue
{
	char			dv_char;
	int				dv_int;
	unsigned int	dv_uint;
	long long		dv_long;
	float			dv_float;
	double			dv_double;
	char*			dv_str;
	long long		dv_time;
};

struct FieldData
{
	unsigned short	field;
	DataValue		value;
};


// class DataAdapter
// {
// public:
// 
// 	enum DataType
// 	{
// 		DT_CHAR,
// 		DT_INT,
// 		DT_LONG,		// 64位整型
// 		DT_FLOAT,
// 		DT_DOUBLE,
// 		DT_STR		// 字符串
// 	};
// 
// 	std::vector<DataField> m_fields;
// };

#endif