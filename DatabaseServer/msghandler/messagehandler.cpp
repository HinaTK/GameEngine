
#include "messagehandler.h"
#include "../table/tb_login.h"
#include "common/protocol/l_dbprotocol.h"
//#include "messageheader.h"


MessageHandler::MessageHandler()
{
	m_function_list[IProtocol::MT_TEST]					= HandlerItem(&MessageHandler::Test, sizeof(IProtocol::Test));
	m_function_list[IProtocol::MT_L_DB_LOGIN]			= HandlerItem(&MessageHandler::UserLogin, sizeof(IProtocol::LDBLogin));
}

void MessageHandler::HandleMessage( char * msg )
{
	IProtocol::MessageHeader * header = (IProtocol::MessageHeader *)msg;
	if (header->msg_type >= IProtocol::MT_MSG_END)
	{
		return;
	}
	(this->*m_function_list[header->msg_type].func)(msg);
}

void MessageHandler::Test(char *msg)
{
	IProtocol::Test *test = (IProtocol::Test *)msg;
	printf("%d", test->c);
}

void MessageHandler::UserLogin( char * msg )
{
// 	IProtocol::LDBLogin * login = (IProtocol::LDBLogin *)msg;
// 	
// 
// 	DataCache::DATAVALUE_VECTOR **field_data = TB_Login::Instance().GetCache()->m_data[login->account];
// 	if (field_data == 0)
// 	{
// 		// 在cache找不到，查找数据库
// 		printf("account = %d, password = %d\n",login->account, login->passward);
// 		DataValue val;
// 		val.dv_uint = 0;
// 		DataCache::DATAVALUE_VECTOR *data = new DataCache::DATAVALUE_VECTOR(TB_Login::MAX_FIELD);
// 		(*data)[TB_Login::ACCOUNT].dv_uint = login->account;
// 		(*data)[TB_Login::PASSWORD].dv_uint = login->passward;
// 		TB_Login::Instance().GetCache()->m_data.Push(login->account, data);
// 	}
// 	else
// 	{
// 		printf("raccount = %d, rpassword = %d\n",(**field_data)[TB_Login::ACCOUNT].dv_uint, (**field_data)[TB_Login::PASSWORD].dv_uint);
// 		//printf("raccount = %d, rpassword = %d\n",field_data[TB_Login::ACCOUNT].dv_uint, field_data[TB_Login::PASSWORD].dv_uint);
// 	}
}


