
#include "guimi.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/tinyxml/tinyxml.h"
#include "lib/include/timemanager/gametime.h"
#include "main/mainthread.h"


NewFrame::NewFrame()
: m_net_manager(&m_thread_manager)
{

}

NewFrame::~NewFrame()
{
	
}

// ��ܳ�ʼ��
bool NewFrame::Init(const char *config)
{
	m_lua_interface.LoadFile(config);
	//m_lua_interface.LoadFile("/../scripts/test.lua");
	m_lua_interface.OnInit();
// 	m_lua_interface.OnUpdate(1, 2);
// 	m_lua_interface.OnAccept(12, "127.0.0.1");
	return true;
}

bool NewFrame::Run()
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
			m_lua_interface.OnTest();
		}
		else if (strncmp(cmd_buf, "update", 4) == 0)
		{
			m_lua_interface.OnUpdate(0, 0);
		}
		printf(cmd_buf);
		printf("\n");
	}
	
	return true;
}

// ���ܸ���
void NewFrame::Update(unsigned int interval, time_t now)
{

}

void NewFrame::Loop()
{
	m_net_manager.Update();
}

void NewFrame::OuterRecv(GameMsg *msg)
{

}


void NewFrame::InnerRecv(GameMsg *msg)
{

}



void NewFrame::Exit()
{
	// �����˳����߳�Ҳ��֮�˳�

	printf("game server exit\n");
}

void NewFrame::Wait()
{
}



