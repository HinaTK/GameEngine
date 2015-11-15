
#include "nethandler.h"
#include "netmanager.h"

NetHandler::NetHandler(NetManager *manager, int type, BaseMsg *msg)
: m_handle(0)
, m_sock(0)
, m_net_manager(manager)
, m_type(type)
, m_call_back_handle(manager->RegisterMsgHandle(msg))
, m_call_back(msg->m_call_back)
{
}

NetHandler::~NetHandler()
{
	m_net_manager->RemoveMsgHandle(m_call_back_handle);
}

