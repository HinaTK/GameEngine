#include <stdio.h>
#include <time.h>
#include "databaseframe.h"
#include "log/log.h"
#include "common/protocol/messageheader.h"

bool DatabaseFrame::Init()		// ��ܳ�ʼ��
{
	return true;
}


void DatabaseFrame::OnRecv(NetID userID, char *msg, unsigned int length)
{
	m_message_handler.HandleMessage(msg);
// 	static int num = 1;
// 	printf("num = %d, recv = %s\n",num++, msg);  
// 	OnSend(userID, msg, length);
	
}

void DatabaseFrame::InteanalRecv(NetID net_id, char *msg, unsigned int length)
{
	printf("recv ...%s\n", msg);
	//m_message_handler.HandleMessage(msg);
}

void DatabaseFrame::Update(time_t now)	// ���ܸ���
{
	m_time_event_manager.Update(now);
	//StmtSelect();
	//StmtInsert();
	//StmtUpdate();
	//StmtDelete();
	//exit(0);
}

void DatabaseFrame::Exit()
{
	// �����˳����߳�Ҳ��֮�˳�
	printf("database server exit\n");
}

