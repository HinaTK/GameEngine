

#include "net_base.h"
#include "netcommon.h"
#include "accepter.h"
#include "baselistener.h"
#include "socketmsg.h"
#include "common/protocol/messageheader.h"


NetBase::NetBase()
: m_is_run(true)
, m_listen_thread(NULL)
{

}

NetBase::~NetBase()
{

	for (MSG_HANDLER::iterator itr = m_msg_handler.Begin(); itr != m_msg_handler.End(); ++itr)
	{
		delete (*itr)->msg[BaseMsg::MSG_ACCEPT];
		delete (*itr)->msg[BaseMsg::MSG_RECV];
		delete (*itr)->msg[BaseMsg::MSG_DISCONNECT];
		delete (*itr);
	}

	for (NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin(); itr != m_net_handler.End(); ++itr)
	{
		NetCommon::Close((*itr)->m_sock);
		delete (*itr);
	}

	if (m_listen_thread)
	{
		delete m_listen_thread;
	}
}

unsigned int NetBase::AddMsgHandler(MsgCallBack *call_back)
{
	MsgHandler *mh = new MsgHandler;
	mh->msg[BaseMsg::MSG_ACCEPT] = new AcceptMsg(call_back);
	mh->msg[BaseMsg::MSG_RECV] = new RecvMsg(call_back);
	mh->msg[BaseMsg::MSG_DISCONNECT] = new DisconnectMsg(call_back);
	return m_msg_handler.Insert(mh);
}

bool NetBase::InitServer(char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back)
{
	printf("Init Server ip = %s, port = %d\n", ip, port);
	SOCKET net_id = 0;
	NetCommon::StartUp();
	if (!NetCommon::Init(ip, port, backlog, net_id))
	{
		delete accepter;
		delete call_back;
		return false;
	}

	accepter->m_msg_index = AddMsgHandler(call_back);
	accepter->m_sock = net_id;
	AddNetHandler(accepter);
	printf("Init Server Success\n");
	return true;
}

NetHandle NetBase::SyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back)
{
	SOCKET sock = NetCommon::Connect(ip, port);
	if (sock == INVALID_SOCKET)
	{
		delete listener;
		delete call_back;
		return INVALID_NET_HANDLE;
	}
	
	listener->m_msg_index = AddMsgHandler(call_back);
	listener->m_sock = sock;
	return AddNetHandler(listener);
}


void NetBase::AsyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back, int flag /*= 0*/)
{
	SOCKET sock = NetCommon::Connect(ip, port);
	if (sock == INVALID_SOCKET)
	{
		return;
	}
	listener->m_msg_index = AddMsgHandler(call_back);
	listener->m_sock = sock;
	SocketMsg::AddHandler ah;
	ah.data.flag = flag;
	ah.data.listener = (void *)listener;
	m_thread->PushMsg(new ThreadMsg(SocketMsg::STM_ADD_HANDLER, -1, sizeof(SocketMsg::AddHandler), (const char *)&ah));
}


void *Loop(void *arg)
{
	NetBase *manager = (NetBase *)arg;
	manager->Loop();
	return NULL;
}


NetHandle NetBase::AddNetHandler(NetHandler *handler)
{
	InitNetHandler(handler);
	handler->m_handle = m_net_handler.Insert(handler);
	return handler->m_handle;
}


void NetBase::RemoveHandler(NetHandle handle, int reason)
{
	RemoveInfo info{ handle, reason };
	m_invalid_handle.Push(info);
}

void NetBase::AddReplaceHandler(NetHandler *handler)
{
	m_net_handler.Erase(handler->m_handle);
	handler->m_handle = m_net_handler.Insert(handler);
	m_replace_handler.Push(handler);
}

bool NetBase::Send(NetHandle handle, const char *buf, unsigned int length)
{
	MutexLock lock(&m_net_mutex);
	NET_HANDLER_ARRAY::iterator itr = m_net_handler.Find(handle);
	if (itr == m_net_handler.End())
	{
		return false;
	}

	if ((*itr)->Type() == NetHandler::LISTENER)
	{
		Listener *listener = (Listener *)(*itr);
		if (listener != NULL)
		{
			listener->Send(buf, length);
			listener->RegisterWriteFD();
			return true;
		}
	}
	return false;
}

void NetBase::PushMsg(NetHandler *handler, unsigned short msg_type, const char *data, unsigned int len)
{
	m_queue.Push(new GameMsg(handler->m_msg_index, msg_type, handler->m_handle, data, len));
}

bool NetBase::Update()
{
	static GameMsg *msg;
	bool ret = m_queue.Size() > 0;
	do
	{
		if (m_queue.Pop(msg)/* && msg != NULL*/)
		{
			if (msg->handle >= 0)
			{
				m_msg_handler[msg->msg_index]->msg[msg->msg_type]->Recv(msg);
			}
			delete msg;
		}
		else break;
	} while (true);
	return ret;
}


void NetBase::Listen()
{
	m_listen_thread = new std::thread(::Loop, this);
}

void NetBase::Exit()
{
	m_is_run = false;
}

void NetBase::Wait()
{
	if (m_listen_thread != NULL)
	{
		m_listen_thread->join();
	}
}


