
#include "gameframe.h"
#include "common/datastructure/msgqueue.h"
#include "common/commonfunction.h"
#include "common/protocol/messageheader.h"
#include "libcommon/serverconfig.h"
#include "poolconfig/test.h"


GameFrame::GameFrame()
{

}

GameFrame::~GameFrame()
{
	Exit();
}

bool GameFrame::InitConfig()
{
	if (!m_net_manager.InitServer(
		ServerConfig::Instance().m_ip[ServerConfig::GAME_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::GAME_GATEWAY].port,
		ServerConfig::Instance().m_server[ServerConfig::GAME_GATEWAY].backlog,
		m_gateway_server_net_id))
	{
		return false;
	}

	if (!m_net_manager.ConnectServer(
		ServerConfig::Instance().m_ip[ServerConfig::DATABASE_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_GAME].port,
		m_database_server_net_id))
	{
		return false;
	}

// 	ListenServer();
// 	ListenClient();
	
	struct Test
	{
		Test() :header(0){}
		IProtocol::MessageHeader	header;
		char a;
		short b;
		int c;
	};
	Test test;
	test.a = 1;
	test.b = 2;
	test.c = 3;
	test.header.msg_len = (sizeof(Test));
	m_net_manager.Send(m_database_server_net_id, (const char *)&test, test.header.msg_len);
// 	send(m_database_server_net_id, (const char *)&test, 1288, 0);
	return this->Init();
}


int main()
{
    if (!GameFrame::Instance().InitConfig())
    {
		Function::WindowsPause();
		return 0;
    }

	GameFrame::Instance().Run();
	Function::WindowsPause();
	
    return 0;
}