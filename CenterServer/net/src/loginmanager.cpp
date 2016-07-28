
#include "loginmanager.h"
#include "threadproto.h"
#include "net/netthread.h"


LoginManager::LoginManager(NetThread *t)
: m_thread(t)
{

}

LoginManager::~LoginManager()
{

}

void LoginManager::OnLogin(Proto::csLogin *login)
{
	ThreadProto::LoadRole lr;
	memcpy(lr.account, login->account, ACCOUNT_SIZE);
	lr.sid = login->sid;
	m_thread->GetManager()->SendMsg(ThreadProto::TP_LOAD_ROLE, m_thread->GetThreadID(), sizeof(ThreadProto::LoadRole), (const char *)&lr, m_thread->GetID());
}

void LoginManager::OnCreateRole(Proto::csCreateRole *role)
{
	ThreadProto::SaveRole sr;
	memcpy(sr.account, role->account, ACCOUNT_SIZE);
	sr.sid = role->sid;
	memcpy(sr.name, role->name, GAME_NAME_SIZE);
	m_thread->GetManager()->SendMsg(ThreadProto::TP_SAVE_ROLE, m_thread->GetThreadID(), sizeof(ThreadProto::SaveRole), (const char *)&sr, m_thread->GetID());
}
