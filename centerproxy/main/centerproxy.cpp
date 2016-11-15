
#include "centerproxy.h"
#include "net/netthread.h"
#include "lib/include/frame/main.h"

CenterProxy::CenterProxy()
{

}

CenterProxy::~CenterProxy()
{

}

bool CenterProxy::Init()
{
	m_thread_manager.Register(new NetThread(&m_thread_manager, 1));
	m_thread_manager.Register(new NetThread(&m_thread_manager, 2));
	return m_thread_manager.Init();
}

bool CenterProxy::Start()
{
	m_thread_manager.Start();
	this->Run();
	return true;
}

bool CenterProxy::Cmd(char *buf)
{
	return false;
}

void CenterProxy::Exit()
{

}

void CenterProxy::Wait()
{

}

GAME_MAIN(CenterProxy);