

#include "gatewayframe.h"
#include "libcommon/serverconfig.h"
#include "common/commonfunction.h"
//#include "common/datastructure/hashlist.h"
#include "common/protocol/messageheader.h"


GatewayFrame::GatewayFrame()
{
	//m_ex_com.SetFrame(this);
}

GatewayFrame::~GatewayFrame()
{
	Exit();
}

bool GatewayFrame::InitConfig()
{
// 	if (!m_in_com.ConnectServer(
// 		ServerConfig::Instance().m_ip[ServerConfig::GAME_SERVER],
// 		ServerConfig::Instance().m_server[ServerConfig::GAME_GATEWAY].port,
// 		m_game_server_net_id))
// 	{
// 		return false;
// 	}
// 	if (!m_in_com.ConnectServer(
// 		ServerConfig::Instance().m_ip[ServerConfig::LOGIN_SERVER],
// 		ServerConfig::Instance().m_server[ServerConfig::LOGIN_GATEWAY].port,
// 		m_login_server_net_id))
// 	{
// 		return false;
// 	}

	if (!m_net_manager.InitServer(
		ServerConfig::Instance().m_ip[ServerConfig::GATEWAY_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::GATEWAY_CLIENT].port,
		ServerConfig::Instance().m_server[ServerConfig::GATEWAY_CLIENT].backlog,
		m_gate_net_id, true))
	{
		return false;
	}

	return Init();
}


int main()
{
    if (!GatewayFrame::Instance().InitConfig())
    {
		Function::WindowsPause();
		return 0;
    }
	GatewayFrame::Instance().Run();
	Function::WindowsPause();
    return 0;
}
