
#include <stdio.h>
#include <string.h>
#include "databaseframe.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/cache/datacache.h"
#include "common/globalclass.h"
#include "common/commonfunction.h"
#include "cache/datamapmanager.h"
#include "../database/database.h"
#include "lib/include/redis/redis.h"
#include "lib/include/frame/listener.h"

DatabaseFrame::DatabaseFrame()
{

}

DatabaseFrame::~DatabaseFrame()
{
	Exit();
}

class RedisListener : public Listener
{
public:
	RedisListener(NetManager *manager, int call_back_handle) 
		: Listener(manager)
		, m_call_back_handle(call_back_handle){}
	~RedisListener(){}
	bool AnalyzeBuf()
	{
		const char *buf = m_recv_buf.GetBuf();
		GameMsg *msg = new GameMsg(m_handle, buf, m_recv_buf.Length());
		msg->call_back_handle = m_call_back_handle;
		m_net_manager->GetMsgQueue()->Push(msg);
		return true;
	};

private:
	int m_call_back_handle;
};

class RedisCallBack : public MsgCallBack
{
public:
	RedisCallBack(){}
	~RedisCallBack(){}

	void	Recv(GameMsg *msg)
	{
		printf("fuck\n");
	}
};

RedisCallBack g_call_back;

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

// 	if (!DataBase::Instance().Init(
// 		ServerConfig::Instance().m_db_ip,
// 		ServerConfig::Instance().m_db_name,
// 		ServerConfig::Instance().m_user_name,
// 		ServerConfig::Instance().m_password
// 		))
// 	{
// 		printf("connect database error\n");
// 		return false;
// 	}
// 	printf("connect database success\n");

	DataMapManager::Instance().Init();

	int handle = m_net_manager.RegisterCallBack(&g_call_back);

	Redis redis;
	RedisListener *listener = new RedisListener(&m_net_manager, handle);
	redis.SetNetManager(&m_net_manager);
	
	redis.Connect("192.168.1.105", 6379, listener);
// 	char *command = "set name jiaming\r\n";
// 	redis.Command(command, strlen(command));

	char *command = "get name\r\n";
	redis.Command(command, strlen(command));
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
