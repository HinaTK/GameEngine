

#include "netmanager.h"
#include "netcommon.h"
#include "baseaccepter.h"
#include "baselistener.h"
#include "socketthread.h"
#include "socketmsg.h"
#include "common/protocol/messageheader.h"
#include "lib/include/common/mem.h"


NetManager::NetManager(ThreadManager *tm)
: m_thread(new SocketThread(tm, this))
{
	// 将线程注册到管理器，因为不需要再自己释放指针
	tm->Register(m_thread);
}

NetManager::~NetManager()
{
	for (MSG_HANDLER::iterator itr = m_msg_handler.Begin(); itr != m_msg_handler.End(); ++itr)
	{
		delete (*itr)->msg[BaseMsg::MSG_ACCEPT]->m_call_back;
		delete (*itr)->msg[BaseMsg::MSG_ACCEPT];
		delete (*itr)->msg[BaseMsg::MSG_RECV];
		delete (*itr)->msg[BaseMsg::MSG_DISCONNECT];
		delete (*itr)->msg[BaseMsg::MSG_CONNECT];
		delete (*itr);
	}
}


bool NetManager::InitServer(char *ip, unsigned short port, int backlog, MsgCallBack *call_back)
{
	return InitServer(ip, port, backlog, new BaseAccepter(m_thread), call_back);
}

bool NetManager::InitServer(char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back)
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
	m_thread->AddNetHandler(accepter);
	printf("Init Server Success\n");
	return true;
}


NetHandle NetManager::SyncConnect(const char *ip, unsigned short port, MsgCallBack *call_back)
{
	return SyncConnect(ip, port, new BaseListener(m_thread), call_back);
}

NetHandle NetManager::SyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back)
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
	return m_thread->AddNetHandler(listener);
}


void NetManager::AsyncConnect(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back, int flag /*= 0*/)
{
	SOCKET sock = NetCommon::Connect(ip, port);
	if (sock == INVALID_SOCKET)
	{
		return;
	}
	listener->m_msg_index = AddMsgHandler(call_back);
	listener->m_sock = sock;
	SocketMsg::AddHandler ah;
	ah.flag = flag;
	ah.listener = (void *)listener;
	m_thread->PushMsg(new ThreadMsg(SocketMsg::STM_ADD_HANDLER, -1, sizeof(SocketMsg::AddHandler), (const char *)&ah));
}


unsigned int NetManager::AddMsgHandler(MsgCallBack *call_back)
{
	MsgHandler *mh = new MsgHandler;
	mh->msg[BaseMsg::MSG_ACCEPT] = new AcceptMsg(call_back);
	mh->msg[BaseMsg::MSG_RECV] = new RecvMsg(call_back);
	mh->msg[BaseMsg::MSG_DISCONNECT] = new DisconnectMsg(call_back);
	mh->msg[BaseMsg::MSG_CONNECT] = new ConnectMsg(call_back);
	return m_msg_handler.Insert(mh);
}


// void NetManager::AddReplaceHandler(NetHandler *handler)
// {
// 	m_net_handler.Erase(handler->m_handle);
// 	handler->m_handle = m_net_handler.Insert(handler);
// 	m_replace_handler.Push(handler);
// }
// 

void NetManager::Send(NetHandle handle, unsigned int length, const char *buf)
{
	m_thread->PushMsg(new ThreadMsg(SocketMsg::STM_SEND_MSG, handle, length, buf));
}


void NetManager::PushMsg(NetHandler *handler, unsigned short msg_type, const char *data, unsigned int len)
{
	m_queue.Push(m_msg_manager.Alloc(handler->m_msg_index, msg_type, handler->m_handle, data, len));
}

GameMsg	* NetManager::CreateMsg(unsigned int msg_index, unsigned short msg_type, NetHandle handle, unsigned int len)
{
	return m_msg_manager.Alloc(msg_index, msg_type, handle, len);
}

bool NetManager::Update()
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
			m_msg_manager.Free(msg);
		}
		else break;
	} while (true);
	return ret;
}



