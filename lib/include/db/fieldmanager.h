
#ifndef FIELD_MANAGER_H
#define FIELD_MANAGER_H

#include <vector>
#include <string>
#include "module.h"
#include "rolefield.h"
#include "lib/include/rapidjson/define.h"

// todo 做一下内存池
class Field;
class MysqlHandler;
class FieldManager : public DBModule
{
public:
	FieldManager(MysqlHandler *mysql, char *name);
	~FieldManager(){}

	
	void	Register(Field *field);
	bool	Load();
	bool	Save(RoleField *rf);

protected:
	std::string	m_table_name;
	std::string m_base_sql;
	std::vector<Field *> m_manager;
	MysqlHandler *m_mysql_handle;
	rapidjson::StringBuffer m_s;
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
};

#endif // !FIELD_MANAGER_H

