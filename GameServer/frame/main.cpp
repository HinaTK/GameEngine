
#include <stdio.h>
#include <time.h>
#include "gameframe.h"
#include "common/protocol/messageheader.h"
#include "libtinyxml.h"


bool GameFrame::Init()		// ��ܳ�ʼ��
{
	return true;
}

void GameFrame::InteanalRecv( NetID net_id, char *msg, UInt16 length )
{
	if (msg == NULL || length < sizeof(EProtocol::MessageHeader))
	{
		return;
	}
// 	static int num = 1;
// 	printf("GameFrame num = %d, recv = %s\n",num++, msg);  
// 	Send(net_id, msg, length);
	
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

