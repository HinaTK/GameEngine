
#include "messagehandler.h"
#include "net/netthread.h"
#include "protocol/msgid.h"

MessageHandler::MessageHandler(NetThread *t)
: m_thread(t)
, m_login_manager(t->GetLoginManager())
{
	memset(m_function_list, 0, sizeof(m_function_list));

	m_function_list[Proto::CS_LOGIN]		= HandlerItem(&MessageHandler::CSLogin,			sizeof(Proto::csLogin));
	m_function_list[Proto::CS_CREATE_ROLE]	= HandlerItem(&MessageHandler::CSCreateRole,	sizeof(Proto::csCreateRole));
}

void MessageHandler::HandleMessage(GameMsg *msg)
{
	// todo ¶Ï¿ªÁ¬½Ó
	Router *router = (Router *)msg->data;
	if (*router >= Proto::CENTER_END || m_function_list[*router].length == 0)
	{
		return;
	}

	if (msg->length != m_function_list[*router].length)
	{
		return;
	}

	(this->*m_function_list[*router].func)(msg);
}

