
#include <stdio.h>
#include <time.h>
#include "gameframe.h"
#include "common/protocol/messageheader.h"
#include "libtinyxml.h"


bool GameFrame::Init()		// ��ܳ�ʼ��
{
	return true;
}


void GameFrame::Recv(NetHandle handle, char *msg, unsigned int length)
{

}


void GameFrame::Update(time_t now)	// ���ܸ���
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

