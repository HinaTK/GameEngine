
#include "messagehandler.h"
#include "scene/obj/role.h"
#include "global/temprole.h"
#include "db/proto.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/base/interface.h"

MessageHandler::MessageHandler()
{
	memset(m_function_list, 0, sizeof(m_function_list));

	//m_function_list[Proto::CS_LOGIN]		= HandlerItem(&MessageHandler::CSLogin,			sizeof(Proto::csLogin));
}

void MessageHandler::BeforeMessage(Global *global, TempRole *role, NetMsg &msg)
{
	switch(*(Router *)msg.data)
	{
	case Proto::CS_LOGIN:
		CSLogin(global, role, msg);
		break;
	}
}

bool MessageHandler::HandleMessage(Role *role, NetMsg &msg)
{
	Router *router = (Router *)msg.data;
	if (*router >= Proto::GAME_END || m_function_list[*router].length == 0 || msg.length != m_function_list[*router].length)
	{
		role->Logout();
		return false;
	}

	(this->*m_function_list[*router].func)(role, msg);
	return true;
}

void MessageHandler::CSLogin(Global *global, TempRole *role, NetMsg &msg)
{
 	Proto::csLogin *login = (Proto::csLogin *)msg.data;
	unsigned char md5[64] = { 0 };
	char str_tmp[64] = { 0 };
	login->session[SESSION_SIZE - 1] = 0;
	Base::decrypt128((unsigned char *)login->session, md5);
	// todo Ð´µ½¿âÖÐ£¬·ÀÖ¹Ð¹ÃÜ

	int str_len = ::sprintf(str_tmp, "%s%lld", login->account, login->rid);
	std::string &key = Base::MD5Encrypt((const unsigned char *)str_tmp, str_len);
	if (strcmp((char *)md5, key.c_str()) != 0)
	{
		role->Logout();
		return;
	}
	
	GetManager()->SendMsg(m_thread->GetThreadID(), TProto::S_DB_LOAD_ROLE, login->rid, m_thread->GetID());
	// todo ¼ÓÔØÍæ¼ÒÊý¾Ý
	// todo ÇÐ»»³¡¾°

// 	TProto::LoadRole lr;
// 	lr.handle = msg->handle;
// 	memcpy(lr.account, login->account, ACCOUNT_SIZE);
// 	lr.sid = login->sid;
// 	m_thread->GetManager()->SendMsg(m_thread->GetThreadID(), TProto::TP_LOAD_ROLE, sizeof(TProto::LoadRole), (const char *)&lr, m_thread->GetID());
}
