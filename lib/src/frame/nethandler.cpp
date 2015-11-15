
#include "nethandler.h"
#include "netmanager.h"

NetHandler::NetHandler(NetManager *manager, int type)
: m_handle(0)
, m_sock(0)
, m_net_manager(manager)
, m_type(type)
{
}

NetHandler::~NetHandler()
{
}

