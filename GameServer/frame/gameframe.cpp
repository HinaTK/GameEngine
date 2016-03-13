
#include "gameframe.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/frame/baseaccepter.h"
#include "lib/include/tinyxml/tinyxml.h"
#include "lib/include/timemanager/gametime.h"
#include "lib/chat/interface.h"
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
// 	NetManager *net1 = new NetManager();
// 	net1->InitServer("127.0.0.1", 2346, 16, new BaseAccepter(net1), NULL);
// 
// 	NetManager *net2 = new NetManager();
// 	net2->InitServer("127.0.0.1", 2347, 16, new BaseAccepter(net2), NULL);
	m_thread_manager.Register(ThreadManager::ID_DB, new DBThread(&m_thread_manager));
 	m_thread_manager.Register(ThreadManager::ID_MAIN, new MainThread(&m_thread_manager));	
	m_thread_manager.Register(ThreadManager::ID_CHAT, (BaseThread *)NewChatThread(&m_thread_manager));

	for (unsigned char i = ThreadManager::ID_NET; i < ThreadManager::ID_NET + 1; ++i)
	{
		m_thread_manager.Register(i, new NetThread(&m_thread_manager));
	}
	m_thread_manager.Start();

	
	return true;
}

// 构架更新
void NewFrame::Update(unsigned int interval, time_t now)
{
}

void NewFrame::Start()
{
	while (IsRun())
	{
		char cmd_buf[512] = { 0 };
		gets(cmd_buf);
		if (strncmp(cmd_buf, "exit", 4) == 0)
		{
			SetExit();
		}
		else if (strncmp(cmd_buf, "test", 4) == 0)
		{
            for (int i = 0; i < 1000; ++i)
			{
				m_thread_manager.SendMsg(ThreadManager::ID_FRAME, ThreadManager::ID_CHAT, sizeof(int), (const char *)&i);
			}		
		}
//		printf("%s\n", cmd_buf);
	}
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



