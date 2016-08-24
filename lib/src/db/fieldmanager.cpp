
#include "fieldmanager.h"
#include "field.h"
#include "preparedynamic.h"

FieldManager::FieldManager(MysqlHandler *mysql, char *name)
: m_writer(m_s)
, m_mysql_handle(mysql)
, m_base_sql("REPLACE INTO ")
{
	m_base_sql = m_base_sql + name + "(";
}

bool FieldManager::Load()
{
	// 注册的时候，将字段名字与类关联，那么从数据加载数据出来，并找到对应的类进行反序列化
	return true;
}	

bool FieldManager::Save(RoleField *rf)
{
	int field_size = rf->fields.size();
	if (field_size <= 0)
	{
		return true;
	}
	// todo 需要再做一个管理器管理这个FieldManager，将获得表名还有数据库句柄
	// 下面的std::string定义也可以由这个管理者传入（减少初始化消耗）
	// 并传入角色id
	MysqlPrepareDynamic mp(m_mysql_handle, field_size);
	std::string sql = m_base_sql;
	std::string data = ") VALUES (";
	std::string *temp = new std::string[field_size];
	int num = 0;
	for (int i = 0; i < field_size; ++i)
	{
		m_writer.Reset(m_s);
		temp[num] = "";
		if (!m_manager[i]->Serialize(m_writer, temp[num]))
		{
			// todo write log
			continue;
		}
		sql += m_manager[i]->GetName();
		sql += ",";
		data += "?,";
		mp.BindText(num, (char *)temp[num].c_str(), temp[num].size());
		++num;
	}
	sql.replace(sql.size() - 1, 1, data.replace(data.size() - 1, 1, ");"));
	bool ret = mp.Execute(sql.c_str(), sql.size());
	delete [] temp;

	return ret;
}

void FieldManager::Register(Field *field)
{
	m_manager.push_back(field);
}
