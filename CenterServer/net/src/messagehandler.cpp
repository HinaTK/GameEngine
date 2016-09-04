
#include "messagehandler.h"
#include "threadproto.h"
#include "net/netthread.h"
#include "lib/include/common/serverconfig.h"

MessageHandler::MessageHandler(NetThread *t)
: m_thread(t)
{
	memset(m_function_list, 0, sizeof(m_function_list));

	m_function_list[Proto::CS_LOGIN]		= HandlerItem(&MessageHandler::CSLogin,			sizeof(Proto::csLogin));
	m_function_list[Proto::CS_CREATE_ROLE]	= HandlerItem(&MessageHandler::CSCreateRole,	sizeof(Proto::csCreateRole));
}

void MessageHandler::HandleMessage(NetMsg *msg)
{
	// todo 断开连接
	Router *router = (Router *)msg->data;
	if (*router >= Proto::CENTER_END || m_function_list[*router].length == 0)
	{
		m_thread->RemoveHandler(msg->handle);
		return;
	}

	if (msg->length != m_function_list[*router].length)
	{
		return;
	}

	(this->*m_function_list[*router].func)(msg);
}

void MessageHandler::CSLogin(NetMsg *msg)
{
	Proto::csLogin *login = (Proto::csLogin *)msg->data;
	TProto::LoadRole lr;
	lr.handle = msg->handle;
	memcpy(lr.account, login->account, ACCOUNT_SIZE);
	lr.sid = login->sid;
	m_thread->GetManager()->SendMsg(m_thread->GetThreadID(), TProto::TP_LOAD_ROLE, sizeof(TProto::LoadRole), (const char *)&lr, m_thread->GetID());
}

void MessageHandler::CSCreateRole(NetMsg *msg)
{
	Proto::csCreateRole *role = (Proto::csCreateRole *)msg->data;

	TProto::SaveRole sr;
	sr.handle = msg->handle;
	memcpy(sr.account, role->account, ACCOUNT_SIZE);
	sr.sid = CenterConfig::Instance().sid;
	sr.rid = sr.sid * 100000000 + m_thread->GetIDPool()->GetID();
	// todo sid 根据配置获取
	
	memcpy(sr.name, role->name, GAME_NAME_SIZE);
	m_thread->GetManager()->SendMsg(m_thread->GetThreadID(), TProto::TP_SAVE_ROLE, sizeof(TProto::SaveRole), (const char *)&sr, m_thread->GetID());
}

