
#include "loginframe.h"
#include "common/commonfunction.h"
#include "common/protocol/messageheader.h"
#include "common/protocol/msgcode.h"

bool LoginFrame::Init()
{
	return true;
}


void LoginFrame::Recv(GameMsg *msg)
{
// 	if (!Function::ProtocolDecode(msg->data, msg->length))
// 	{
// 		return;
// 	}

// 	struct test
// 	{
// 		int a;
// 		int b;
// 	};
// 
// 	test *c = (test *)msg->data;
// 	Send(msg->handle, (const char *)c, sizeof(test));
	EProtocol::MessageHeader *header = (EProtocol::MessageHeader *)msg->data;
	switch (header->msgid)
	{
	case EProtocol::MT_LOGIN_REQ_CS:
		OnLoginReq(msg->handle, msg->data, msg->length);
		break;
	case EProtocol::MT_LOGIN_CREATE_ROLE_CS:
//		OnCreateRole(net_id, data, length);
		break;
	}
	delete msg;
}

void LoginFrame::Update(unsigned int interval, time_t now)
{

}


void LoginFrame::Exit()
{

}


void LoginFrame::Wait()
{

}
