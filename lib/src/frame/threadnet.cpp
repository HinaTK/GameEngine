
#include "threadnet.h"
#include "listener.h"
#include "netcommon.h"
#include "socketmsg.h"

ThreadNet::ThreadNet(ThreadManager *manager, void *arg)
: BaseThread(manager, arg)
{

}

ThreadNet::~ThreadNet()
{
	for (NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin(); itr != m_net_handler.End(); ++itr)
	{
		NetCommon::Close((*itr)->m_sock);
		delete (*itr);
	}
}


void ThreadNet::Init(void *arg)
{
	m_net_manager = (NetManager *)arg;
}

NetHandle ThreadNet::AddNetHandler(NetHandler *handler)
{
	InitNetHandler(handler);
	handler->m_handle = m_net_handler.Insert(handler);
	return handler->m_handle;
}

void ThreadNet::RemoveHandler(NetHandle handle, int reason)
{
	RemoveInfo info{ handle, reason };
	m_invalid_handle.Push(info);
}

void ThreadNet::RecvData(short type, int sid, int len, const char *data)
{
	switch (type)
	{
	case SocketMsg::STM_ADD_HANDLER:
		AddHandler(data);
	case SocketMsg::STM_SEND_MSG:
		SendMsg(sid, len, data);
	default:
		break;
	}
}

void ThreadNet::AddHandler(const char *data)
{
	SocketMsg::AddHandler::Data *ad = (SocketMsg::AddHandler::Data *)data;
	SocketMsg::AddHandlerRet::Data ard;
	NetHandler *handler = (NetHandler *)ad->listener;
	ard.handle = AddNetHandler(handler);
	ard.flag = ad->flag;
	m_net_manager->PushMsg(handler, BaseMsg::MSG_ACCEPT, (const char *)&ard, sizeof(SocketMsg::AddHandlerRet::Data));
}

void ThreadNet::SendMsg(NetHandle handle, int length, const char *data)
{
	NET_HANDLER_ARRAY::iterator itr = m_net_handler.Find(handle);
	if (itr == m_net_handler.End())
	{
		return;
	}

	if ((*itr)->Type() == NetHandler::LISTENER)
	{
		Listener *listener = (Listener *)(*itr);
		if (listener != NULL)
		{
			listener->Send(data, length);
			listener->RegisterWriteFD();
		}
	}
}
