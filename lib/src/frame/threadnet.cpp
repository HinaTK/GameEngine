
#include "threadnet.h"
#include "listener.h"
#include "netcommon.h"
#include "socketmsg.h"

ThreadNet::ThreadNet(ThreadManager *manager)
: BaseThread(manager, NULL)
{
	m_name = "socket";
}

ThreadNet::~ThreadNet()
{
	for (NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin(); itr != m_net_handler.End(); ++itr)
	{
		NetCommon::Close((*itr)->m_sock);
		delete (*itr);
	}
}

NetHandle ThreadNet::AddNetHandler(NetHandler *handler)
{
	InitNetHandler(handler);
	handler->m_handle = m_net_handler.Insert(handler);
	return handler->m_handle;
}

void ThreadNet::RemoveHandler(NetHandle handle, int err, int reason)
{
	RemoveInfo info;
	info.handle = handle;
	info.show.err = err;
	info.show.reason = reason;
	m_invalid_handle.Push(info);
}


void ThreadNet::PushNetMsg(NetMsg &msg)
{
	m_queue.Push(msg);
}

void ThreadNet::PushNetMsg(NetHandler *handler, NetMsgType msg_type, const char *data, unsigned int len)
{
	NetMsg msg(handler->m_msg_index, msg_type, handler->m_handle, len);
	m_net_memory.Alloc(&msg.data, data, len);
	m_queue.Push(msg);
}

void ThreadNet::RecvData(short type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case SocketMsg::STM_ADD_HANDLER:
		AddHandler(data);
	case SocketMsg::STM_SEND_MSG:
		SendMsg(sid, len, data);
	case SocketMsg::STM_REMOVE_HANDLER:
		RemoveHandler(*(NetHandle *)data, 0);
		ClearHandler();
	default:
		break;
	}
}

void ThreadNet::AddHandler(const char *data)
{
	SocketMsg::AddHandler *sa = (SocketMsg::AddHandler *)data;
	SocketMsg::AddHandlerRet::Data ard;
	NetHandler *handler = (NetHandler *)sa->listener;
	ard.handle = AddNetHandler(handler);
	ard.flag = sa->flag;
	PushNetMsg(handler, BaseMsg::MSG_ACCEPT, (const char *)&ard, sizeof(SocketMsg::AddHandlerRet::Data));
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