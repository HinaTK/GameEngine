
#ifndef FIELD_MANAGER_H
#define FIELD_MANAGER_H

#include <vector>
#include <string>
#include "lib/include/rapidjson/define.h"

class Field;
class FieldManager
{
public:
	FieldManager();
	~FieldManager(){}

	void	Register(Field *field);

	void	Serialize(std::string &str);

protected:
	std::vector<Field *> m_manager;

	rapidjson::StringBuffer m_s;
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
};

#endif // !FIELD_MANAGER_H

