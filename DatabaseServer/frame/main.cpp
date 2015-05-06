
#include <stdio.h>
#include <time.h>
#include "databaseframe.h"
#include "lib/include/log/log.h"
#include "lib/include/common/memoryvl.h"
#include "lib/include/rpc/rpcserver.h"
#include "database/database.h"
#include "table/tb_login.h"
#include "cache/datamapmanager.h"
#include "common/protocol/messageheader.h"


bool DatabaseFrame::Init()		// ��ܳ�ʼ��
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
	unsigned int server_id = RPCServer::GetServerID(msg->data);
	delete msg;
	//m_message_handler.HandleMessage(msg);
}

void DatabaseFrame::Update(unsigned int interval, time_t now)	// ���ܸ���
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
