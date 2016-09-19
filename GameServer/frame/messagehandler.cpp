
#include "messagehandler.h"
#include "scene/obj/role.h"
#include "lib/include/common/serverconfig.h"

MessageHandler::MessageHandler()
{
	memset(m_function_list, 0, sizeof(m_function_list));

	m_function_list[Proto::CS_LOGIN]		= HandlerItem(&MessageHandler::CSLogin,			sizeof(Proto::csLogin));
}

bool MessageHandler::HandleMessage(Role *role, NetMsg &msg)
{
	Router *router = (Router *)msg.data;
	if (*router >= Proto::GAME_END || m_function_list[*router].length == 0)
	{
		role->Logout();
		return false;
	}

	if (msg.length != m_function_list[*router].length)
	{
		role->Logout();
		return false;
	}

	(this->*m_function_list[*router].func)(role, msg);
	return true;
}

void MessageHandler::CSLogin(Role *role, NetMsg &msg)
{
 	Proto::csLogin *login = (Proto::csLogin *)msg.data;
	// todo 校验md5
	// todo 加载玩家数据
	// todo 切换场景

// 	TProto::LoadRole lr;
// 	lr.handle = msg->handle;
// 	memcpy(lr.account, login->account, ACCOUNT_SIZE);
// 	lr.sid = login->sid;
// 	m_thread->GetManager()->SendMsg(m_thread->GetThreadID(), TProto::TP_LOAD_ROLE, sizeof(TProto::LoadRole), (const char *)&lr, m_thread->GetID());
}
