
#ifndef FIELD_MANAGER_H
#define FIELD_MANAGER_H

#include <vector>
#include <string>
#include "module.h"
#include "lib/include/rapidjson/define.h"

// todo 做一下内存池
class Field;
class FieldManager : public DBModule
{
public:
	FieldManager();
	~FieldManager(){}

	
	void	Register(Field *field);
	bool	Load();
	bool	Save(char *name);

protected:
	std::vector<Field *> m_manager;

	rapidjson::StringBuffer m_s;
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
};

#endif // !FIELD_MANAGER_H

