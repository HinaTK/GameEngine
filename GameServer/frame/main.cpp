
#include <stdio.h>
#include <time.h>
#include "gameframe.h"
#include "common/protocol/messageheader.h"
#include "lib/include/tinyxml/tinyxml.h"


bool GameFrame::Init()		// ��ܳ�ʼ��
{
	return true;
}


void GameFrame::Recv(GameMsg *msg)
{

}

void GameFrame::Update(unsigned int interval, time_t now)	// ���ܸ���
{
	//m_time_event_manager.Update(now);
	//StmtSelect();
	//StmtInsert();
	//StmtUpdate();
	//StmtDelete();
	//exit(0);
}

void GameFrame::Exit()
{
	// �����˳����߳�Ҳ��֮�˳�

	printf("game server exit\n");
}

void GameFrame::Wait()
{

}
