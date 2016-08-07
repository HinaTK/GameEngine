
#include "game.h"
#include "db/dbthread.h"
#include "net/netthread.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/frame/main.h"
#include "lib/include/common/serverconfig.h"




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
	GameConfig::Instance().Init();
	m_thread_manager.Register(new NetThread(&m_thread_manager));
	m_db_id = m_thread_manager.Register(new DBThread(&m_thread_manager));
	return true;
}


bool NewFrame::Start()
{
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
	printf("game server exit\n");
}

void NewFrame::Wait()
{

}

GAME_MAIN(NewFrame);

