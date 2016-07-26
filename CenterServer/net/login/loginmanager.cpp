
#include "loginmanager.h"
#include "main/center.h"
#include "net/netthread.h"
#include "message/threadproto.h"

LoginManager::LoginManager(NetThread *t)
: m_thread(t)
, m_cur_thread_id(0)
{

}

LoginManager::~LoginManager()
{

}

ThreadID LoginManager::GetThreadID()
{
	if (m_cur_thread_id >= Center::MAX_DB_THREAD)
	{
		m_cur_thread_id = 0;
	}
	return Center::Instance().db_thread_id[m_cur_thread_id++];
}

void LoginManager::OnLogin(Account account, ServerID server_id)
{
	ThreadProto::LoadRole lr;
	memcpy(lr.account, account, ACCOUNT_SIZE);
	lr.server_id = server_id;
	m_thread->GetManager()->SendMsg(ThreadProto::TP_LOAD_ROLE, GetThreadID(), sizeof(ThreadProto::LoadRole), (const char *)&lr, m_thread->GetID());
}
