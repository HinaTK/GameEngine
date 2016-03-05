

#include "net_base.h"
#include "common/protocol/messageheader.h"
#include "netcommon.h"
#include "accepter.h"
#include "baselistener.h"


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
		return false;
	}

	accepter->m_msg_index = AddMsgHandler(call_back);
	accepter->m_sock = net_id;
	AddNetHandler(accepter);
	printf("Init Server Success\n");
	return true;
}

NetHandle NetBase::ConnectServer(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back)
{
	printf("connect to Server ip = %s, port = %d\n", ip, port);

	NetCommon::StartUp();
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		printf("Create socket error\n");
		NetCommon::CleanUp();
		return INVALID_NET_HANDLE;
	}

	if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		printf("Connect server error %d\n", NetCommon::Error());
		NetCommon::Close(sock);
		NetCommon::CleanUp();
		return INVALID_NET_HANDLE;
	}

	printf("Connect Server Success\n");
	listener->m_msg_index = AddMsgHandler(call_back);
	listener->m_sock = sock;
	return AddNetHandler(listener);
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
	GameMsg *game_msg = new GameMsg(handler->m_msg_index, msg_type, handler->m_handle, data, len);
	m_queue.Push(game_msg);
}

void NetBase::Update()
{
	static GameMsg *msg;
	do
	{
		if (m_queue.Pop(msg) && msg != NULL)
		{
			if (msg->handle >= 0)
			{
				m_msg_handler[msg->msg_index]->msg[msg->msg_type]->Recv(msg);
				// 内存交给下游处理
				// delete (*msg);
			}
			else delete msg;
		}
		else break;
	} while (true);
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


