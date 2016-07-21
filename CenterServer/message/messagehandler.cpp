
#include "messagehandler.h"
#include "net/netthread.h"
#include "protocol/msgid.h"
#include "message/proto.h"

MessageHandler::MessageHandler(NetThread *t)
: m_thread(t)
{
	memset(m_function_list, 0, sizeof(m_function_list));

	m_function_list[Proto::CS_LOGIN] = HandlerItem(&MessageHandler::CSLogin, sizeof(Proto::csLogin));
}

void MessageHandler::HandleMessage(GameMsg *msg)
{
	// todo ¶Ï¿ªÁ¬½Ó
	Router *router = (Router *)msg->data;
	if (*router >= Proto::CENTER_END || m_function_list[*router].length == 0)
	{
		return;
	}

	if (*router != m_function_list[*router].length)
	{
		return;
	}

	(this->*m_function_list[*router].func)(msg);
}

void MessageHandler::CSLogin(GameMsg *msg)
{
	Proto::csLogin *login = (Proto::csLogin *)msg->data;
	m_thread->GetLoginManager()->OnLogin(login->plat_name, login->server_id);
	printf("fsdfsdf\n");
// 	EProtocol::CSUserLogin * ul = (EProtocol::CSUserLogin *)msg;
// 	printf("account = %d, password = %d\n",ul->account, ul->password);
// 	IProtocol::LDBLogin ldl;
// 	ldl.account = ul->account;
// 	ldl.passward = ul->password;
// 	InCom::Instance().OnSend(LoginFrame::Instance().m_database_server_net_id, (const char *)&ldl, sizeof(ldl));
}

