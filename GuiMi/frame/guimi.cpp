
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

// 框架初始化
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

// 构架更新
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
	// 进程退出，线程也随之退出

	printf("game server exit\n");
}

void NewFrame::Wait()
{
}



