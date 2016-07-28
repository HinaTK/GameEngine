
#include "loginmanager.h"
#include "net/netthread.h"
#include "message/threadproto.h"

LoginManager::LoginManager(NetThread *t)
: m_thread(t)
{

}

LoginManager::~LoginManager()
{

}

void LoginManager::OnLogin(Account account, ServerID server_id)
{
	ThreadProto::LoadRole lr;
	memcpy(lr.account, account, ACCOUNT_SIZE);
	lr.server_id = server_id;
	m_thread->GetManager()->SendMsg(ThreadProto::TP_LOAD_ROLE, m_thread->GetThreadID(), sizeof(ThreadProto::LoadRole), (const char *)&lr, m_thread->GetID());
}
