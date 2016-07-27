
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

//	bool	Save();
	void	Register(Field *field);

	bool	Serialize(std::string &str);

protected:
	std::vector<Field *> m_manager;

	rapidjson::StringBuffer m_s;
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
};

#endif // !FIELD_MANAGER_H

