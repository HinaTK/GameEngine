
#include "guimi.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/tinyxml/tinyxml.h"
#include "lib/include/timemanager/gametime.h"


NewFrame::NewFrame()
: m_o_call_back(this)
, m_i_call_back(this)
{

}

NewFrame::~NewFrame()
{
	Exit();
}


bool NewFrame::InitConfig()
{
	return this->Init();
}

// ��ܳ�ʼ��
bool NewFrame::Init()
{
	m_lua_engine.LoadLuaFile("/luafile/test.lua");
	m_lua_engine.GetGlobalProc("Main");
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



