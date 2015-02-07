
#ifndef TEST_MYSQL_H
#define TEST_MYSQL_H

#include "database/database.h"
#include "table/tb_login.h"

namespace TestMysql
{
	void Insert()
	{
		TB_Login test(0, "login", DataBase::Instance().GetStmt());
		test.Init();
		test.m_ID = 123;
		test.m_ACCOUNT = 456;
		test.m_NAME = "jia";
		test.Insert();
	}
}

#endif