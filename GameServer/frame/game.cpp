
#include "game.h"
#include "db/dbthread.h"
#include "net/netthread.h"
#include "log/loghandler.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/frame/main.h"
#include "lib/include/frame/socketthread.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/log/logrole.h"



NewFrame::NewFrame()
: m_db_id(0)
{

}

NewFrame::~NewFrame()
{

}

// 框架初始化

bool NewFrame::Init()
{
	SocketThread *st = new SocketThread(&m_thread_manager);
	m_thread_manager.Register(st);
	m_thread_manager.Register(new NetThread(&m_thread_manager, st));

	LogDBMsg::LogRegister reg[] =
	{
		{0, "log_gold", "(rid,log)", 10, 1000}
	};
	
	m_db_id = m_thread_manager.Register(new DBThread(&m_thread_manager));
	m_log_id = m_thread_manager.Register(new LogRole(&m_thread_manager, 1, reg));
	return m_thread_manager.Init();
}


bool NewFrame::Start()
{
	if (!m_thread_manager.Ready()) return false;
	m_thread_manager.Start();
	return true;
}

// 构架更新
void NewFrame::Update(unsigned int interval, time_t now)
{
}



void NewFrame::Exit()
{
	m_thread_manager.Exit();
}

void NewFrame::Wait()
{

}

bool NewFrame::Cmd(char *buf)
{
	if (strcmp(buf, "test") == 0)
	{
		// char buf[128];
		// int len = LogRole::MakeLog(0, 112233, buf, "fff=%d,ggg=%s", 223344, "333rrr");
		// m_thread_manager.SendMsg(m_log_id, LogDBMsg::LDM_WRITE, len, buf);
		 m_thread_manager.SendMsg(m_log_id, LogDBMsg::LDM_WRITE, LogGold(112233, 512));
		return true;
	}
	return false;
}

GAME_MAIN(NewFrame);


