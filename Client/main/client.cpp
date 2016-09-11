
#include "client.h"
#include "net/netthread.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/main.h"

Client::Client()
{

}

Client::~Client()
{

}

bool Client::Init()
{
	m_thread_manager.Register(new NetThread(&m_thread_manager));
	return m_thread_manager.Init();
}

bool Client::Start()
{
	m_thread_manager.Start();
	return true;
}

bool Client::Cmd(char *buf)
{
	return false;
}

void Client::Exit()
{

}

void Client::Wait()
{

}

GAME_MAIN(Client);