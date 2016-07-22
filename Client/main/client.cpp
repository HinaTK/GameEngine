
#include "client.h"
#include "net/netthread.h"
#include "lib/include/common/serverconfig.h"


Client::Client()
{

}

Client::~Client()
{

}

bool Client::Init()
{
	m_thread_manager.Register(new NetThread(&m_thread_manager));
	return true;
}

void Client::Start()
{
	m_thread_manager.Start();
	this->Run();
}

void Client::Cmd(char *buf)
{

}

void Client::Exit()
{

}

void Client::Wait()
{

}

