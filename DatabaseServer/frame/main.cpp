
#include <stdio.h>
#include <time.h>
#include "databaseframe.h"
#include "log/log.h"
#include "database/database.h"
#include "table/tb_login.h"
#include "common/protocol/messageheader.h"
#include "libcommon/memoryvl.h"

bool DatabaseFrame::Init()		// ��ܳ�ʼ��
{
	TB_Login test(0, "login", DataBase::Instance().GetStmt());
	test.Init();

	if (0)
	{
		test.m_ID = 123;
		test.m_ACCOUNT = 456;
		test.m_PASSWORD = 789;
		test.m_NAME.length = 3;
		test.m_NAME.data = (char *)MemoryVL::Instance().Malloc(test.m_NAME.length);
		memcpy(test.m_NAME.data, "jia", test.m_NAME.length);
		test.Insert();
	}
	
	test.m_ID = 0;
	if (!test.Select())
	{
		return false;
	}

	test.BindResult();
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
// 	mysql_stmt_execute(DataBase::Instance().GetStmt());           //ִ�����������ص�Ԥ����
// 	mysql_stmt_bind_result(DataBase::Instance().GetStmt(), params); //���ڽ�������е��������ݻ���ͳ��Ȼ���������󶨣�����
// 	
// //	mysql_stmt_store_result(DataBase::Instance().GetStmt());      //�Ա������mysql_stmt_fetch()�����ܷ��ػ�������
// 
// 	while (mysql_stmt_fetch(DataBase::Instance().GetStmt()) == 0) //���ؽ�����е���һ��
// 		printf("%d\t%s\n", id, name);
	return true;
}

void DatabaseFrame::Recv(GameMsg *msg)
{
	m_message_handler.HandleMessage(msg);
}

void DatabaseFrame::Update(time_t now)	// ���ܸ���
{
	m_time_event_manager.Update(now);
	//StmtSelect();
	//StmtInsert();
	//StmtUpdate();
	//StmtDelete();
	//exit(0);
}

void DatabaseFrame::Exit()
{
	m_message_handler.Exit();
	printf("database server exit\n");
}

