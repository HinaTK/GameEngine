
#include "messagehandler.h"
#include "net/netthread.h"
#include "protocol/msgid.h"

MessageHandler::MessageHandler(NetThread *t)
: m_thread(t)
{
	memset(m_function_list, 0, sizeof(m_function_list));
}

void MessageHandler::HandleMessage(GameMsg *msg)
{
	if (msg->msg_type >= Proto::CENTER_END || m_function_list[msg->msg_type].length == 0)
	{
		return;
	}

	m_function_list[msg->msg_type].func(msg);
}

void MessageHandler::CSLogin(GameMsg *msg)
{
// 	printf("fsdfsdf");
// 	EProtocol::CSUserLogin * ul = (EProtocol::CSUserLogin *)msg;
// 	printf("account = %d, password = %d\n",ul->account, ul->password);
// 	IProtocol::LDBLogin ldl;
// 	ldl.account = ul->account;
// 	ldl.passward = ul->password;
// 	InCom::Instance().OnSend(LoginFrame::Instance().m_database_server_net_id, (const char *)&ldl, sizeof(ldl));
}

