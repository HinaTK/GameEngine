
#include <stdio.h>
#include <time.h>
#include "databaseframe.h"
#include "lib/include/log/log.h"
#include "lib/include/common/memoryvl.h"
#include "database/database.h"
#include "table/tb_login.h"
#include "cache/datamapmanager.h"
#include "common/protocol/messageheader.h"


bool DatabaseFrame::Init()		// 框架初始化
{
	TB_Login test(0, "login", DataBase::Instance().GetStmt());
	test.Init();

	if (0)
	{
		test.m_ID = 111;
		test.m_ACCOUNT = 222;
		test.m_PASSWORD = 333;
		//memset(test.m_NAME.data, 0, 32);
		test.SetBufferLength(TB_Login::NAME, 4);
		memcpy(test.m_NAME.data, "xian", 4);
		test.Insert();
	}
	
	if (1)
	{
		//test.SetCondition()
	}
	test.m_ID = 0;
	if (!test.Select())
	{
		return false;
	}

	while (test.HasResult())
	{
		printf("%d\n", test.m_ID);
		printf("%d\n", test.m_ACCOUNT);
		printf("%s\n", test.m_NAME.data);
	}

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

void DatabaseFrame::Recv(GameMsg *msg)
{
	m_message_handler.HandleMessage(msg);
}

void DatabaseFrame::Update(time_t now)	// 构架更新
{
	//StmtSelect();
	//StmtInsert();
	//StmtUpdate();
	//StmtDelete();
	//exit(0);
}

void DatabaseFrame::Exit()
{
	m_message_handler.Exit();
	DataMapManager::Instance().Exit();

	printf("database server exit\n");
}


void DatabaseFrame::Wait()
{
	m_message_handler.Wait();
	DataMapManager::Instance().Wait();
}
