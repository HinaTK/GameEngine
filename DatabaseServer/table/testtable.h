#ifndef TESTTABLE_H
#define TESTTABLE_H

#include "../database/gamemysqlstmt.h"
#include "cache/dataadapter.h"

class TestTable:public GameMysqlStmt
{
public:
	
	~TestTable(){};

	static TestTable &Instance()
	{
        static TestTable instance("testtable");
		return instance;
	}
	enum Field
	{
		ID,
		ROLE_ID,
		MAX_FIELD,
	};
	VAR_DEFINE(UInt32, ID);
	VAR_DEFINE(UInt32, ROLE_ID);

	std::string *	GetFields(){return m_field_name;}

	UInt32			GetMaxField(){return TestTable::MAX_FIELD;}

	MYSQL_BIND *	GetParam(){return m_param;}

	void			Show();

private:
	
	TestTable(std::string table_name);

	MYSQL_BIND m_param[MAX_FIELD];
	std::string m_field_name[MAX_FIELD];
};

#endif
