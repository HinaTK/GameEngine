
#include "messagehandler.h"
#include "table/tb_login.h"
#include "common/protocol/l_dbprotocol.h"
#include "timemanager/gametime.h"
//#include "messageheader.h"

void *FlushQueue(void * arg)
{
	static const unsigned int sleepTime = 60 * 1000;
	MessageHandler *handler = (MessageHandler *)arg;
	CircleQueue<GameMsg *> data_queue = handler->DataQueue();
	while (true)
	{
		if (!data_queue.IsEmpty())
		{
			GameMsg **msg = data_queue.Pop();
			// 处理数据
			delete (*msg);
		}
		else
		{
			GameTime::GameSleep(50);
		}
	}
	return NULL;
}

MessageHandler::MessageHandler()
{
	m_flush_thread.Create(FlushQueue, this);
// 	m_function_list[IProtocol::MT_TEST]					= HandlerItem(&MessageHandler::Test, sizeof(IProtocol::Test));
// 	m_function_list[IProtocol::MT_L_DB_LOGIN]			= HandlerItem(&MessageHandler::UserLogin, sizeof(IProtocol::LDBLogin));
}

MessageHandler::~MessageHandler()
{
	//MessageBox(NULL, L"初始化socket失败", L"消息", MB_OK);
}

void MessageHandler::HandleMessage(GameMsg *msg)
{
	do 
	{
		IProtocol::MessageHeader * header = (IProtocol::MessageHeader *)msg->data;
		if (header->msg_type >= IProtocol::MT_MAX_DATABASE_SERVER_TYPE || header->msg_type <= IProtocol::MT_MIN_DATABASE_SERVER_TYPE)
		{
			break;
		}
		if (header->msg_type == IProtocol::MT_PUSH_INTO_DATA_QUEUE)
		{
			m_queue.Push(msg);
			return;
		}
		(this->*m_function_list[header->msg_type].func)(msg->data);
	} while (false);
	
	delete msg;
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


