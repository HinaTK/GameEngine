#include <stdio.h>
#include <time.h>
#include "databaseframe.h"
#include "log/log.h"
#include "common/protocol/messageheader.h"

bool DatabaseFrame::Init()		// 框架初始化
{
	return true;
}

void DatabaseFrame::Recv(GameMsg *msg)
{
	m_message_handler.HandleMessage(msg);
}

void DatabaseFrame::Update(time_t now)	// 构架更新
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
	m_message_handler.Exit();
	printf("database server exit\n");
}

