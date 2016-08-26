
#include "fieldmanager.h"
#include "field.h"
#include "preparestatic.h"
#include "result.h"

FieldManager::FieldManager(MysqlHandler *mysql, char *name, unsigned short field_len, FieldManager::CreateField *field)
: m_writer(m_s)
, m_val(new std::string[field_len])
, m_field_len(field_len)
, m_all_field(field)
, m_mp(mysql, field_len + 1)
{
	m_base_sql = "REPLACE INTO ";
	m_base_sql += name;
	m_base_sql += " (rid,";
	std::string temp = "SELECT ";
	for (unsigned short i = 0; i < m_field_len; ++i)
	{
		temp += m_all_field[i].name;
		temp += ",";
	}
	temp.replace(temp.size() - 1, 1, " FROM ");
	temp += name;
	temp += " WHERE rid=?;";
	m_load = new MysqlPrepareStatic(mysql, 1, temp.c_str());
}

FieldManager::~FieldManager()
{
	if (m_load != NULL)
	{
		delete m_load;
	}

	if (m_val != NULL)
	{
		delete [] m_val;
		m_val = NULL;
	}
}

bool FieldManager::Load(RoleField *rf)
{
	// 注册的时候，将字段名字与类关联，那么从数据加载数据出来，并找到对应的类进行反序列化
	m_load->BindLong(0, &rf->rid);
	if (m_load->Execute())
	{
		char *temp = NULL;
		int len = 0;
		int num = 0;
		MysqlResult mr(m_load);
		while(m_load->HasResult() && num < m_field_len)
		{
			temp = mr.ReadStr(num, len);
			if (temp != NULL)
			{
				// todo （测试）数据库null字段

				Field *field = m_all_field[num].func();
				field->Deserialize(temp);
				rf->fields.push_back(field);
			}
			else
			{
				// todo write log
			}
			++num;
		}
	}
	return true;
}	

bool FieldManager::Save(RoleField *rf)
{
	int field_size = rf->fields.size();
	if (field_size <= 0) return true;
	else if (field_size > m_field_len)
	{
		// todo 写log
		return false;
	}
	
	m_mp.BindLong(0, &rf->rid);
	m_sql = m_base_sql;
	m_data = ") VALUES (?,";

	int num = 1;
	for (int i = 0; i < field_size; ++i)
	{
		m_writer.Reset(m_s);
		m_val[num] = "";
		if (!rf->fields[i]->Serialize(m_writer, m_val[num]))
		{
			// todo write log
			continue;
		}
		m_sql += rf->fields[i]->GetName();
		m_sql += ",";
		m_data += "?,";
		m_mp.BindText(num, (char *)m_val[num].c_str(), m_val[num].size());
		++num;
	}

	bool ret =  false;
	if (num > 1)
	{
		m_sql.replace(m_sql.size() - 1, 1, m_data.replace(m_data.size() - 1, 1, ");"));
		ret = m_mp.Execute(m_sql.c_str(), m_sql.size());
	}

	return ret;
}
