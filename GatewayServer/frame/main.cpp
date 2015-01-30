
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

void GatewayFrame::Recv(NetHandle handle, char *msg, UInt16 length)
{
	//Send()
	printf("%s\n", msg);
}

void GatewayFrame::Update(time_t now)
{

}

void GatewayFrame::Exit()
{

}
