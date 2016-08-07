
#ifndef TEST_NET_H
#define TEST_NET_H

#include "lib/include/frame/netmanager.h"
#include "lib/include/frame/message.h"
#include "lib/include/base/interface.h"
#include "lib/include/thread/threadmanager.h"
#include "lib/include/http/httpaccepter.h"
#include "lib/include/http/httplistener.h"

namespace TestNet
{
	class CallBack : public MsgCallBack
	{
	public:
		CallBack()
			: MsgCallBack(){}
		~CallBack(){}

		void	Accept(NetHandle handle, const char *ip){}

	    void	Recv(GameMsg *msg)
		{
			printf("dddddd\n");
		}

		void	Disconnect(NetHandle handle, int err, int reason){}
	};

	class CallBack2 : public MsgCallBack
	{
	public:
		CallBack2(NetManager *manager)
			: MsgCallBack(), m_manager(manager){}
		~CallBack2(){}

		void	Accept(NetHandle handle, const char *ip){}

		void	Recv(GameMsg *msg)
		{
			printf("dddddd2\n");
			m_manager->Send(msg->handle, sizeof("this is my name"), "this is my name");
		}

		void	Disconnect(NetHandle handle, int err, int reason){}

		NetManager *m_manager;
	};

	void Test1()
	{
// 		ThreadManager thread_manager;
// 		NetManager *net_manager = new NetManager(&thread_manager);
// 		for(int i = 0; i < 10000; ++i)
// 		{
// 			if (net_manager->SyncConnect("127.0.0.1", 12347, new CallBack()) == -1)
// 			{
// 				printf("can not connect server %d\n", i);
// 				break;
// 			}
// 			Time::Sleep(2);
// 		}
// 		printf("test end ...\n");
	}

	void Test2()
	{
// 		char buf[8];
// 		ThreadManager thread_manager;
// 		NetManager *net_manager = new NetManager(&thread_manager);
// 		for (int i = 0; i < 100; ++i)
// 		{
// 			NetHandle handle = net_manager->SyncConnect("127.0.0.1", 12347, new CallBack());
// 			if (handle == -1)
// 			{
// 				printf("can not connect server %d\n", i);
// 				break;
// 			}
// 			Time::Sleep(2);
// 			(*(int *)buf) = rand() % 20000 - 10000;
// 			net_manager->Send(handle, 8, buf);
// 		}
// 		printf("test end ...\n");
	}

	void Test3()
	{
		ThreadManager thread_manager;
		NetManager m_net_manager(&thread_manager);
		m_net_manager.InitServer("127.0.0.1", 12345, 2, new HttpAccepter(m_net_manager.GetThread(), HttpAccepter::CB_FIELD), new CallBack2(&m_net_manager));
		thread_manager.Start();
		while (true)
		{
			if (!m_net_manager.Update())
			{
				Time::Sleep(10);
			}
		}
	}
}

#endif