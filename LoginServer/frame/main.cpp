
#include "loginframe.h"

bool LoginFrame::Init()
{
	return true;
}



void LoginFrame::OnRecv( NetID user_id, char *msg, UInt16 length )
{
	m_message_handler.HandleMessage(msg, length);
}

void LoginFrame::Update()
{

}

void LoginFrame::Exit()
{

}

