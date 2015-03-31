
#include <string.h>
#include "databaseframe.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/cache/datacache.h"
#include "common/globalclass.h"
#include "common/commonfunction.h"
#include "cache/datamapmanager.h"
#include "../database/database.h"

DatabaseFrame::DatabaseFrame()
{

}

DatabaseFrame::~DatabaseFrame()
{
	Exit();
}

bool DatabaseFrame::InitConfig()
{
	if (!m_net_manager.InitServer(
		ServerConfig::Instance().m_ip[ServerConfig::DATABASE_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_LOGIN].port,
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_LOGIN].backlog,
		m_login_net_id))
	{
		return false;
	}
	printf("m_login_net_id = %d\n", m_login_net_id);

	if (!m_net_manager.InitServer(
		ServerConfig::Instance().m_ip[ServerConfig::DATABASE_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_GAME].port,
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_GAME].backlog,
		m_game_net_id))
	{
		return false;
	}
	printf("m_game_net_id = %d\n", m_game_net_id);

	if (!DataBase::Instance().Init(
		ServerConfig::Instance().m_db_ip,
		ServerConfig::Instance().m_db_name,
		ServerConfig::Instance().m_user_name,
		ServerConfig::Instance().m_password
		))
	{
#ifdef WIN32
		printf("connect database error\n");
#endif
		return false;
	}
	printf("connect database success\n");

	DataMapManager::Instance().Init();
	return Init();
}


int main()
{
    if (!DatabaseFrame::Instance().InitConfig())
    {
		Function::WindowsPause();
		return 0;
    }
	//Log::Instance().Error("writelog");
	DatabaseFrame::Instance().Run();
	Function::WindowsPause();
    return 0;
}
