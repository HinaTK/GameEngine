
#include "gateway.h"
#include "net/netthread.h"
#include "lib/include/frame/main.h"
#include "lib/include/common/serverconfig.h"


Gateway::Gateway()
{

}

Gateway::~Gateway()
{

}

bool Gateway::Init()
{
	for (unsigned int i = 0; i < GatawayConfig::Instance().m_server.size(); ++i)
	{
		m_thread_manager.Register(new NetThread(&m_thread_manager, i));
	}
	
	return m_thread_manager.Init();
}

bool Gateway::Start()
{
	m_thread_manager.Start();
	return true;
}

void Gateway::Exit()
{

}

void Gateway::Wait()
{

}

GAME_MAIN(Gateway);