
#ifndef FIELD_MANAGER_H
#define FIELD_MANAGER_H

#include <vector>
#include <string>
#include <functional>
#include "module.h"
#include "rolefield.h"
#include "preparedynamic.h"
#include "lib/include/rapidjson/define.h"

class Field;
class MysqlHandler;
class MysqlPrepareStatic;
class FieldManager : public DBModule
{
public:

	struct CreateField
	{
		char *name;
		std::function<Field *()> func;
	};

	FieldManager(MysqlHandler *mysql, char *name, unsigned short field_len, CreateField *field);
	~FieldManager();


	bool	Load(RoleField *rf);
	bool	Save(RoleField *rf);

protected:
	std::string 	m_base_sql;
	std::string 	m_sql;
	std::string 	m_data;
	std::string 	*m_val;
	unsigned short	m_field_len;
	CreateField 	*m_all_field;
	
	MysqlPrepareDynamic m_mp;
	MysqlPrepareStatic	*m_load;
	rapidjson::StringBuffer m_s;
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
};

#endif // !FIELD_MANAGER_H

