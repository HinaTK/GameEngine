
#include <stdio.h>
#include <string.h>
#include "dataframe.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/timemanager/gametime.h"
#include "lib/include/cache/datacache.h"
#include "lib/include/redis/redis.h"
#include "lib/include/frame/listener.h"
#include "common/globalclass.h"
#include "common/commonfunction.h"
#include "cache/datamapmanager.h"



NewFrame::NewFrame()
    : m_i_call_back(this)
{

}

NewFrame::~NewFrame()
{
	Exit();
}

bool NewFrame::InitConfig()
{
	if (!m_net_manager.InitServer(
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].ip,
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].port,
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].backlog,
        new Accepter(&m_net_manager), &m_i_call_back))
	{
		return false;
	}


// 	if (!DataBase::Instance().Init(
// 		ServerConfig::Instance().m_db_ip,
// 		ServerConfig::Instance().m_db_name,
// 		ServerConfig::Instance().m_user_name,
// 		ServerConfig::Instance().m_password
// 		))
// 	{
// 		printf("connect database error\n");
// 		return false;
// 	}
// 	printf("connect database success\n");

	return Init();
}

bool NewFrame::Init()		// 框架初始化
{
	Frame::Init();

	// 	TB_Login test(0, "login", DataBase::Instance().GetStmt());
	// 	test.Init();
	// 
	// 	if (0)
	// 	{
	// 		test.m_id = 111;
	// 		test.FIELD(account) = 222;
	// 		test.FIELD(password) = 333;
	// 		//memset(test.m_NAME.data, 0, 32);
	// 		test.SetBufferLength(TB_Login::name, 4);
	// 		memcpy(test.m_name.data, "xian", 4);
	// 		test.Insert();
	// 	}
	// 	
	// 	if (1)
	// 	{
	// 		//test.SetCondition()
	// 	}
	// 	test.m_id = 0;
	// 	if (!test.Select())
	// 	{
	// 		return false;
	// 	}
	// 
	// 	while (test.HasResult())
	// 	{
	// 		printf("%d\n", test.m_id);
	// 		printf("%d\n", test.m_account);
	// 		printf("%s\n", test.m_name.data);
	// 	}

	//	char *query = "select id,name from login;";
	// 	char *query = "SELECT id, name FROM login;";
	// 	if (mysql_stmt_prepare(DataBase::Instance().GetStmt(), query, strlen(query)))
	// 	{
	// 		//fprintf(stderr, "mysql_stmt_prepare: %s\n", mysql_error(conn));
	// 		return false;
	// 	}
	// 
	// 	int id; 
	// 	char name[20];
	// 
	// 	MYSQL_BIND params[2];
	// 	memset(params, 0, sizeof(params));
	// 	params[0].buffer_type = MYSQL_TYPE_LONG;
	// 	params[0].buffer = &id;
	// 	params[1].buffer_type = MYSQL_TYPE_STRING;
	// 	params[1].buffer = name;
	// 	params[1].buffer_length = 10;
	// 
	// //	mysql_stmt_bind_param(DataBase::Instance().GetStmt(), params);
	// 	mysql_stmt_execute(DataBase::Instance().GetStmt());           //执行与语句句柄相关的预处理
	// 	mysql_stmt_bind_result(DataBase::Instance().GetStmt(), params); //用于将结果集中的列与数据缓冲和长度缓冲关联（绑定）起来
	// 	
	// //	mysql_stmt_store_result(DataBase::Instance().GetStmt());      //以便后续的mysql_stmt_fetch()调用能返回缓冲数据
	// 
	// 	while (mysql_stmt_fetch(DataBase::Instance().GetStmt()) == 0) //返回结果集中的下一行
	// 		printf("%d\t%s\n", id, name);
	return true;
}

static unsigned long long begin = GameTime::Instance().MilliSecond();
void NewFrame::Recv(GameMsg *msg)
{
    int ret = *(int *)msg->data;
//     if (ret % 100 == 0)
//     {
//         printf("ret = %d\n", ret);
//     }

	Send(msg->handle, msg->data, msg->length);

	delete msg;
	//m_message_handler.HandleMessage(msg);
	if (ret <= 1)
	{
		begin = GameTime::Instance().MilliSecond();
	}
	else if (ret >= 10000)
	{
		printf("fuck exit %d\n", GameTime::Instance().MilliSecond() - begin);
		system("pause");
		exit(0);
	}
}

void NewFrame::Update(unsigned int interval, time_t now)	// 构架更新
{
	//StmtSelect();
	//StmtInsert();
	//StmtUpdate();
	//StmtDelete();
	//exit(0);
}

void NewFrame::Exit()
{

	printf("database server exit\n");
}


void NewFrame::Wait()
{

}
