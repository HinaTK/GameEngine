
#include "query.h"
#include "net/netthread.h"
#include "lib/include/frame/main.h"

Query::Query()
{

}

Query::~Query()
{

}

bool Query::Init()
{
	m_thread_manager.Register(new NetThread(&m_thread_manager, 1));
	m_thread_manager.Register(new NetThread(&m_thread_manager, 2));
	return m_thread_manager.Init();
}

bool Query::Start()
{
	m_thread_manager.Start();
	this->Run();
	return true;
}

bool Query::Cmd(char *buf)
{
	return false;
}

void Query::Exit()
{

}

void Query::Wait()
{

}

GAME_MAIN(Query);