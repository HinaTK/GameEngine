#include "testtable.h"
#include <stdio.h>

// #define SETFIELD(field, field_type)\
// 	if (strcmp("int", #field_type) == 0)\
// 	{\
// 		m_adapter.m_fields[field].type = DataAdapter::DT_INT;\
// 		m_adapter.m_fields[field].length = 4;\
// 	}\
	

TestTable::TestTable( std::string table_name ):
GameMysqlStmt(table_name)
{
	m_field_name[TestTable::ID] = "id";
	m_field_name[TestTable::ROLE_ID] = "roleid";

	m_param[TestTable::ID].buffer_type = MYSQL_TYPE_LONG;
	m_param[TestTable::ID].buffer = &FIELD(ID);

	m_param[TestTable::ROLE_ID].buffer_type = MYSQL_TYPE_LONG;
	m_param[TestTable::ROLE_ID].buffer = &FIELD(ROLE_ID);

	/*
		����cache,����Ҫ������ͳһ�ӿڣ�����mysql��cache�Ľӿ�Ҫһ�£����ٸ��Ӷ�;
		��mysql��������m_param�ٵ��÷����ӿڣ�
		Ҳ����Ҫ������m_param������
	*/
//	SETFIELD(TestTable::ID, int);
// 	m_adapter.m_fields[TestTable::ID].type = DataAdapter::DT_INT;
// 	m_adapter.m_fields[TestTable::ID].length = 4;
// 	m_adapter.m_fields[TestTable::ROLE_ID].type = DataAdapter::DT_INT;
// 	m_adapter.m_fields[TestTable::ROLE_ID].length = 4;
}


void TestTable::Show()
{
	while(mysql_stmt_fetch(DataBase::Instance().GetStmt()) == 0) //���ؽ�����е���һ��
         printf("%d\t%d\n", FIELD(ID), FIELD(ROLE_ID));

	//GET_FIELD(id);
    printf("fuck\n");
}
