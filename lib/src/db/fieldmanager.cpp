
#include "fieldmanager.h"
#include "field.h"

FieldManager::FieldManager()
: m_writer(m_s)
{

}

// bool FieldManager::Save()
// {
// 	std::string str = "";
// 	std::string temp = "";
// 	for (std::vector<Field *>::iterator itr = m_manager.begin(); itr != m_manager.end(); ++itr)
// 	{
// 		m_writer.Reset(m_s);
// 		if (!(*itr)->Serialize(m_writer, temp))
// 		{
// 			// todo write log
// 		}
// 		str += temp + ",";
// 	}
// 	if (str == "")
// 	{
// 		return false;
// 	}
// 	str.replace(str.size() - 1, 1, ";");
// 	return true;
// }

void FieldManager::Register(Field *field)
{
	m_manager.push_back(field);
}

bool FieldManager::Serialize(std::string &str)
{
	std::string temp = "";
	for (std::vector<Field *>::iterator itr = m_manager.begin(); itr != m_manager.end(); ++itr)
	{
		m_writer.Reset(m_s);
		if (!(*itr)->Serialize(m_writer, temp))
		{
			// todo write log
		}
		str += temp + ",";
	}
	if (str == "")
	{
		return false;
	}
	str.replace(str.size() - 1, 1, ";");
	return true;
}

