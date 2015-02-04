
#include "gatewayframe.h"
#include "common/protocol/messageheader.h"
#include "common/protocol/messagetype.h"

bool GatewayFrame::Init()
{
	return true;
}

// void GatewayFrame::ExternalRecv( NetID user_id, char *msg, UInt16 length )
// {
// 	EProtocol::MessageHeader * header = (EProtocol::MessageHeader *) msg;
// 	printf("header->msg_type = %d\n", header->msg_type);
// 	printf("header->msg_len = %d\n", header->msg_len);
// 	if (header->msg_type <= EProtocol::LOGIN_PROTOCOL)
// 	{
// 		m_in_com.OnSend(m_login_server_net_id, msg, length);
// 	}
// 	else if (header->msg_type <= EProtocol::GLOBAL_PROTOCOL)
// 	{
// 		//Internal::Instance().OnSend(m_)
// 	}
// 	else if (header->msg_type <= EProtocol::GAME_PROTOCOL)
// 	{
// 		m_in_com.OnSend(m_game_server_net_id, msg, length);
// 	}
// }

void GatewayFrame::Recv(NetHandle handle, char *msg, unsigned int length)
{
	//printf("%s\n", msg);
//	Send(handle, msg, length);
// 	int a = 1234;
// 	Send(handle, (const char *)&a, sizeof(int));

// 	char *b = "123h";
// 	Send(handle, (const char *)b, strlen(b));
 	char *b = "家明a";
	Send(handle, (const char *)b, strlen(b));

// 	char c[6];
// 	c[0] = -27;
// 	c[1] = -82;
// 	c[2] = -74;
// 	c[3] = -26;
// 	c[4] = -104;
// 	c[5] = -114;
// 	Send(handle, (const char *)c, 6);
}

void GatewayFrame::Update(time_t now)
{

}

void GatewayFrame::Exit()
{

}
