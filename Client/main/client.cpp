
#include "client.h"
#include "net/netthread.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/main.h"
#include "lib/include/frame/socketthread.h"

Client::Client()
{

}

Client::~Client()
{

}

bool Client::Init()
{
	SocketThread *st = new SocketThread(&m_thread_manager);
	m_thread_manager.Register(st);
	m_thread_manager.Register(new NetThread(&m_thread_manager, st));
	return m_thread_manager.Init();
}

bool Client::Start()
{
	m_thread_manager.Start();
	this->Run();
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