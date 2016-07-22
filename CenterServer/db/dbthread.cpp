
#include "dbthread.h"
#include "message/threadproto.h"
#include "lib/include/mysql/mysql.h"

DBThread::~DBThread()
{

}

DBThread::DBThread(ThreadManager *manager)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
{

}

void DBThread::Init(void *arg)
{

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
	std::string update = "UPDATE role SET name=? WHERE sid=123;";
	int server_id = 123;
	char *account = "fffhhh222333";
	char *name = "jiaming";
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
	MYSQL_BIND *param2 = new MYSQL_BIND[1];
	memset(param2, 0, sizeof(MYSQL_BIND));

	param2[0].buffer_type = MYSQL_TYPE_STRING;
	param2[0].buffer = name;
	param2[0].buffer_length = strlen(name);
	param2[0].length = 0;

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
	
	delete [] param;
	
	//MYSQL_TYPE_BIT
	mysql_stmt_close(stmt1);
	mysql_stmt_close(stmt2);
	mysql_close(mysql);
}

void DBThread::RecvData(short type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case ThreadProto::TP_LOAD_ROLE:
		test_mysql();
		printf("load role ... %d\n", GetID());
	default:
		break;
	}
}


