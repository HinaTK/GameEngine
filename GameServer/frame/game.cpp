
#include "game.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/frame/baseaccepter.h"
#include "lib/include/tinyxml/tinyxml.h"
#include "lib/include/timemanager/gametime.h"
#include "lib/include/common/serverconfig.h"
//#include "lib/chat/interface.h"
#include "main/mainthread.h"
#include "db/dbthread.h"
#include "net/netthread.h"



NewFrame::NewFrame()
{

}

NewFrame::~NewFrame()
{

}

// 框架初始化
bool NewFrame::Init()
{
	GameConfig::Instance().Init();
//	MainThread *mt = new MainThread(&m_thread_manager);
//	BaseThread *bt = (BaseThread *)NewChatThread(&m_thread_manager);
    NetThread *nt = new NetThread(&m_thread_manager);
		
	return true;
}


void NewFrame::Start()
{
	m_thread_manager.Start();
	while (IsRun())
	{
		char cmd_buf[512] = { 0 };
		gets(cmd_buf);
		if (strncmp(cmd_buf, "exit", 4) == 0)
		{
			SetExit();
		}
	}
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
	printf("game server waiting ...\n");
	m_thread_manager.Wait();
	printf("game server end\n");
}



