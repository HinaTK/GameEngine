
#include "loginframe.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/timemanager/timemanager.h"
#include "common/commonfunction.h"
#include "message/messagetype/msglogin.h"


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
		m_login_server_net_id))
	{
		return false;
	}

	if (!m_net_manager.ConnectServer(
		ServerConfig::Instance().m_ip[ServerConfig::DATABASE_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_LOGIN].port,
		m_database_server_handle))
	{
		return false;
	}
	

	m_rpc_server.Init(&m_net_manager, m_database_server_handle, 999);
	return Init();
}

void LoginFrame::OnLoginReq(NetHandle handle, char *data, unsigned int length)
{
	if (length < sizeof(EProtocol::CSLogin))
	{
		return;
	}

	EProtocol::CSLogin *cl = (EProtocol::CSLogin *)data;

	cl->pname[sizeof(PlatName)-1] = '\0';
	if (std::string(cl->pname) == "")
	{
		return;
	}

	// 去数据库查找数据
	//Send(m_database_server_handle, data, length);
	char buf[16];
	RPCSerializer s(buf, 16);
	m_rpc_server.Call(1, 2, s);
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
