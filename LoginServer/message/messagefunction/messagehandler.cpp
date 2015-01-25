
#include "messagehandler.h"
#include "message/messagetype/msglogin.h"
#include "common/protocol/l_dbprotocol.h"
#include "frame/loginframe.h"

MessageHandler::MessageHandler()
{
	memset(m_function_list, 0, sizeof(m_function_list));
	m_function_list[REAL_TYPE(EProtocol::MT_USER_LOGIN)] = HandlerItem(&MessageHandler::UserLogin,sizeof(EProtocol::CSUserLogin));
}

void MessageHandler::HandleMessage( char * msg, UInt16 length )
{
	EProtocol::MessageHeader * header = (EProtocol::MessageHeader *)msg;
	if (header->msg_type >= EProtocol::MT_LOGIN_END)
	{
		return;
	}
	(this->*m_function_list[header->msg_type].func)(msg, length);
}

void MessageHandler::UserLogin( const char *msg, UInt16 length )
{
// 	printf("fsdfsdf");
// 	EProtocol::CSUserLogin * ul = (EProtocol::CSUserLogin *)msg;
// 	printf("account = %d, password = %d\n",ul->account, ul->password);
// 	IProtocol::LDBLogin ldl;
// 	ldl.account = ul->account;
// 	ldl.passward = ul->password;
// 	InCom::Instance().OnSend(LoginFrame::Instance().m_database_server_net_id, (const char *)&ldl, sizeof(ldl));
}

