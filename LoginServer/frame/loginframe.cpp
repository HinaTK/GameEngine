
#include "loginframe.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/timemanager/timemanager.h"
#include "common/commonfunction.h"


LoginFrame::LoginFrame()
{

}

LoginFrame::~LoginFrame()
{
	Exit();
}

bool LoginFrame::InitConfig()
{
	if (!m_net_manager.InitServer(
		ServerConfig::Instance().m_ip[ServerConfig::LOGIN_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::LOGIN_GATEWAY].port,
		ServerConfig::Instance().m_server[ServerConfig::LOGIN_GATEWAY].backlog,
		m_login_server_net_id, true))
	{
		return false;
	}

// 	if (!m_net_manager.ConnectServer(
// 		ServerConfig::Instance().m_ip[ServerConfig::DATABASE_SERVER],
// 		ServerConfig::Instance().m_server[ServerConfig::DATABASE_LOGIN].port,
// 		m_database_server_net_id))
// 	{
// 		return false;
// 	}
	printf("Init Success %s %d\n", ServerConfig::Instance().m_ip[ServerConfig::LOGIN_SERVER], ServerConfig::Instance().m_server[ServerConfig::LOGIN_GATEWAY].port);
	return Init();
}


int main()
{
    if (!LoginFrame::Instance().InitConfig())
    {
		Function::WindowsPause();
		return 0;
    }

	LoginFrame::Instance().Run();
	Function::WindowsPause();
    return 0;
}
