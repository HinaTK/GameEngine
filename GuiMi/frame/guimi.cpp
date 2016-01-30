
#include "guimi.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/tinyxml/tinyxml.h"
#include "lib/include/timemanager/gametime.h"
#include "main/mainthread.h"


NewFrame::NewFrame()
{

}

NewFrame::~NewFrame()
{
	Exit();
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
	return Frame::Run();
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



