
#include "threadnet.h"
#include "accepter.h"
#include "listener.h"
#include "socketmsg.h"
#include "lib/include/base/netcommon.h"
#include "lib/include/base/function.h"

MsgHandler::MsgHandler(MsgCallBack *call_back)
{
	m_bm[BaseMsg::MSG_ACCEPT] = new AcceptMsg(call_back);
	m_bm[BaseMsg::MSG_RECV] = new RecvMsg(call_back);
	m_bm[BaseMsg::MSG_DISCONNECT] = new DisconnectMsg(call_back);
}

MsgHandler::~MsgHandler()
{
	// 由于call back 由三个类型共同拥有，因此只delete一次
	delete m_bm[BaseMsg::MSG_ACCEPT]->m_call_back;
	delete m_bm[BaseMsg::MSG_ACCEPT];
	delete m_bm[BaseMsg::MSG_RECV];
	delete m_bm[BaseMsg::MSG_DISCONNECT];
}

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

void ThreadNet::RecvData(short type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case SocketMsg::STM_ADD_HANDLER:
		AddHandler(data);
		break;
	case SocketMsg::STM_SEND_MSG:
		Send(sid, len, data);
		break;
	case SocketMsg::STM_REMOVE_HANDLER:
		RemoveHandler(*(NetHandle *)data);
		break;
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
	Recv(handler->m_msg_index, BaseMsg::MSG_ACCEPT, NetMsg(ard.handle, (char *)&ard, sizeof(SocketMsg::AddHandlerRet::Data)));
}

void ThreadNet::RemoveHandler(NetHandle handle, int err, int reason)
{
	m_invalid_handle.Push(RemoveInfo{ handle, NetCommon::ErrInfo{ err, reason } });
}

void ThreadNet::Send(NetHandle handle, int length, const char *data)
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

bool ThreadNet::InitServer(const char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back)
{
	Function::Info("Init Server ...", ip, port);
	SOCKET net_id = 0;
	NetCommon::StartUp();
	if (!NetCommon::Init(ip, port, backlog, net_id))
	{
		delete accepter;
		delete call_back;
		Function::Info("Init Server ip=%s, port=%d Fail", ip, port);
		return false;
	}

	accepter->m_msg_index = m_msg_handler.Insert(new MsgHandler(call_back)); 
	accepter->m_sock = net_id;
	AddNetHandler(accepter);
	Function::Info("Init Server ip=%s, port=%d Success", ip, port);
	return true;
}

NetHandle ThreadNet::SyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back)
{
	SOCKET sock = NetCommon::Connect(ip, port);
	if (sock == INVALID_SOCKET)
	{
		delete listener;
		delete call_back;
		return INVALID_NET_HANDLE;
	}

	listener->m_msg_index = m_msg_handler.Insert(new MsgHandler(call_back));
	listener->m_sock = sock;
	return AddNetHandler(listener);
}

void ThreadNet::AsyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back, int flag /*= 0*/)
{
	SOCKET sock = NetCommon::Connect(ip, port);
	if (sock == INVALID_SOCKET)
	{
		delete listener;
		delete call_back;
		return;
	}
	listener->m_msg_index = m_msg_handler.Insert(new MsgHandler(call_back));
	listener->m_sock = sock;
	SocketMsg::AddHandler ah;
	ah.flag = flag;
	ah.listener = (void *)listener;
	PushMsg(ThreadMsg(SocketMsg::STM_ADD_HANDLER, -1, sizeof(SocketMsg::AddHandler), (const char *)&ah, GetMemory()));
}

void ThreadNet::Recv(unsigned short msg_index, NetMsgType msg_type, NetMsg &msg)
{
	m_msg_handler[msg_index]->Recv(msg_type, msg);
}
