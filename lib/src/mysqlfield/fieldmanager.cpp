
#include "fieldmanager.h"
#include "field.h"

FieldManager::FieldManager()
: m_writer(m_s)
{

}

void FieldManager::Register(Field *field)
{
	m_manager.push_back(field);
}

void FieldManager::Serialize(std::string &str)
{
	str = "";
	std::string temp = "";
	for (std::vector<Field *>::iterator itr = m_manager.begin(); itr != m_manager.end(); ++itr)
	{
		m_writer.Reset(m_s);
		if (!(*itr)->Serialize(m_writer, temp))
		{
			// todo дlog
		}
		str += temp + ",";
	}
	str.replace(str.size() - 1, 1, ";");
}

