
#include "dbthread.h"
#include "threadproto.h"
#include "lib/include/mysql/mysql.h"
#include "lib/include/common/argsplit.h"

DBThread::~DBThread()
{

}

DBThread::DBThread(ThreadManager *manager)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
, m_manager(this)
{
	m_name = "db";
}

bool DBThread::Run()
{
	return false;
}

void test_mysql()
{
	MYSQL *mysql = mysql_init(NULL);
	if (mysql_real_connect(mysql, "127.0.0.1", "jm", "123456", "test_db", 0, 0, 0) == NULL)
	{
		printf("can not connect ...\n");
		return;
	}
	MYSQL_STMT	*stmt1 = mysql_stmt_init(mysql);
	std::string insert = "INSERT INTO role (sid,account) VALUES (?,?);";
	std::string update = "UPDATE role SET name=?,other=? WHERE sid=123;";
	int server_id = 123;
	char *account = "fffhhh222333";
	char *name = "jiaming";
	char *text = "11111jiamingddddd";
	MYSQL_BIND *param = new MYSQL_BIND[2];
	// 这句很重要，不写会挂
	memset(param, 0, sizeof(MYSQL_BIND) * 2);
	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &server_id;
	param[0].length = 0;

	param[1].buffer_type = MYSQL_TYPE_VARCHAR;
	param[1].buffer = account;
	param[1].buffer_length = strlen(account);
	param[1].length = 0;
	
	if (mysql_stmt_prepare(stmt1, insert.c_str(), insert.size()) != 0)
	{
		printf("mysql_stmt_prepare error %s ...\n", mysql_stmt_error(stmt1));
	}
	if (mysql_stmt_bind_param(stmt1, param) != 0)
	{
		printf("mysql_stmt_bind_param error ...\n");
	}
	if (mysql_stmt_execute(stmt1) != 0)
	{
		printf("mysql_stmt_execute error ...\n");
	}

	MYSQL_STMT	*stmt2 = mysql_stmt_init(mysql);
	MYSQL_BIND *param2 = new MYSQL_BIND[2];
	memset(param2, 0, sizeof(MYSQL_BIND) * 2);

	param2[0].buffer_type = MYSQL_TYPE_STRING;
	param2[0].buffer = name;
	param2[0].buffer_length = strlen(name);

	param2[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param2[1].buffer = text;
	param2[1].buffer_length = strlen(text);

	if (mysql_stmt_prepare(stmt2, update.c_str(), update.size()) != 0)
	{
		printf("mysql_stmt_prepare error %s ...\n", mysql_stmt_error(stmt2));
	}
	if (mysql_stmt_bind_param(stmt2, param2) != 0)
	{
		printf("mysql_stmt_bind_param error ...\n");
	}
	if (mysql_stmt_execute(stmt2) != 0)
	{
		printf("mysql_stmt_execute error ...\n");
	}

	delete[] param2;

	server_id = 234;
	account = "11qq22ww33ee";

	param[1].buffer = account;
	param[1].buffer_length = strlen(account);

// 	if (mysql_stmt_prepare(stmt1, insert.c_str(), insert.size()) != 0)
// 	{
// 		printf("mysql_stmt_prepare error %s ...\n", mysql_stmt_error(stmt1));
// 	}
	if (mysql_stmt_bind_param(stmt1, param) != 0)
	{
		printf("mysql_stmt_bind_param error ...\n");
	}
	if (mysql_stmt_execute(stmt1) != 0)
	{
		printf("mysql_stmt_execute error ...\n");
	}
	
	delete [] param;
	
	//MYSQL_TYPE_BIT
	mysql_stmt_close(stmt1);
	mysql_stmt_close(stmt2);
	mysql_close(mysql);
}

void test_mysql2()
{
	MYSQL *mysql = mysql_init(NULL);
	if (mysql_real_connect(mysql, "127.0.0.1", "jm", "123456", "test_db", 0, 0, 0) == NULL)
	{
		printf("can not connect ...\n");
		return;
	}
	MYSQL_STMT	*stmt1 = mysql_stmt_init(mysql);
	std::string select = "SELECT name FROM role WHERE sid=? AND account=?;";
	int server_id = 123;
	char *account = "aabbcc";

	MYSQL_BIND *param = new MYSQL_BIND[2];
	// 这句很重要，不写会挂
	memset(param, 0, sizeof(MYSQL_BIND) * 2);
	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &server_id;

	param[1].buffer_type = MYSQL_TYPE_VARCHAR;
	param[1].buffer = account;
	param[1].buffer_length = strlen(account);
	
	if (mysql_stmt_prepare(stmt1, select.c_str(), select.size()) != 0)
	{
		printf("mysql_stmt_prepare error %s ...\n", mysql_stmt_error(stmt1));
	}
	if (mysql_stmt_bind_param(stmt1, param) != 0)
	{
		printf("mysql_stmt_bind_param error ...\n");
	}
	if (mysql_stmt_execute(stmt1) != 0)
	{
		printf("mysql_stmt_execute error ...\n");
	}


	delete [] param;

	char name[32] = {0};
	unsigned long length = 0;
	
	MYSQL_BIND result;
	memset(&result, 0, sizeof(MYSQL_BIND));
	result.buffer = name;
	result.length = &length;
	result.buffer_length = 32;
	mysql_stmt_bind_result(stmt1, &result);

	while(mysql_stmt_fetch(stmt1) == 0)
	{
		printf("the name is %s\n", name);
	}
	
	mysql_stmt_close(stmt1);
	mysql_close(mysql);
}

void test_mysql3()
{
	MYSQL *mysql = mysql_init(NULL);
	if (mysql_real_connect(mysql, "127.0.0.1", "jm", "123456", "test_db", 0, 0, 0) == NULL)
	{
		printf("can not connect ...\n");
		return;
	}
	MYSQL_STMT	*stmt1 = mysql_stmt_init(mysql);
	std::string select = "SELECT rid FROM role WHERE sid=? AND account=?;";
	int server_id = 123;
	char *account = "aabbcc";

	MYSQL_BIND *param = new MYSQL_BIND[2];
	// 这句很重要，不写会挂
	memset(param, 0, sizeof(MYSQL_BIND) * 2);
	param[0].buffer_type = MYSQL_TYPE_LONG;
	param[0].buffer = &server_id;

	param[1].buffer_type = MYSQL_TYPE_VARCHAR;
	param[1].buffer = account;
	param[1].buffer_length = strlen(account);
	
	if (mysql_stmt_prepare(stmt1, select.c_str(), select.size()) != 0)
	{
		printf("mysql_stmt_prepare error %s ...\n", mysql_stmt_error(stmt1));
	}
	if (mysql_stmt_bind_param(stmt1, param) != 0)
	{
		printf("mysql_stmt_bind_param error ...\n");
	}
	if (mysql_stmt_execute(stmt1) != 0)
	{
		printf("mysql_stmt_execute error ...\n");
	}


	delete [] param;

	int rid = 0;
	char name[32] = {0};
	unsigned long length = 0;
	MYSQL_BIND *result = new MYSQL_BIND;
	memset(result, 0, sizeof(MYSQL_BIND));
	result->buffer_type = MYSQL_TYPE_LONG;
	result->buffer = &rid;
	mysql_stmt_bind_result(stmt1, result);
	// todo 不用也正确，确认一下
	//mysql_stmt_store_result(stmt1);

	while(mysql_stmt_fetch(stmt1) == 0)
	{
		printf("the rid is %d\n", rid);
	}
	
	mysql_stmt_close(stmt1);
	mysql_close(mysql);
}

void DBThread::RecvData(short type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case ThreadProto::TP_LOAD_ROLE_MAX_ID:
		m_manager.LoadRoleMaxID(sid);
		break;
	case ThreadProto::TP_LOAD_ROLE:
		m_manager.LoadRole(sid, len, data);
		printf("load role ... %d\n", GetID());
		break;
	case ThreadProto::TP_SAVE_ROLE_MAX_ID:
		m_manager.SaveRoleMaxID(*(unsigned int *)data);
		break;
	case ThreadProto::TP_SAVE_ROLE:
		m_manager.SaveRole(sid, len, data);
		break;
	default:
		break;
	}
}

bool DBThread::CMD(short type, ThreadID sid, int len, const char *data)
{
	char *buf;
	ArgSplit split((char *)data);
	split.GetArg(&buf);
	if (strcmp(buf, "test") == 0)
	{
		if (split.GetLeft(&buf))
		{
			int id = atoi(buf);
			m_manager.Test(id);
			return true;
		}
	}
	else if (strcmp(buf, "test2") == 0)
	{
		if (split.GetLeft(&buf))
		{
			int id = atoi(buf);
			m_manager.SaveRoleMaxID(id);
			return true;
		}
	}
	return false;
}
