
#include "proxy.h"
#include "net/netthread.h"
#include "filter/filterthread.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/main.h"

Proxy::Proxy()
{

}

Proxy::~Proxy()
{

}

bool Proxy::Init()
{
	m_thread_manager.Register(new FilterThread(&m_thread_manager));
	m_thread_manager.Register(new NetThread(&m_thread_manager));
	return m_thread_manager.Init();
}

bool Proxy::Start()
{
	m_thread_manager.Start();
	this->Run();
	return true;
}

bool Proxy::Cmd(char *buf)
{
	return false;
}

void Proxy::Exit()
{

}

void Proxy::Wait()
{

}

GAME_MAIN(Proxy);