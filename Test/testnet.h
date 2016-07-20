
#ifndef TEST_NET_H
#define TEST_NET_H

#include "lib/include/frame/netmanager.h"
#include "lib/include/frame/message.h"
#include "lib/include/base/interface.h"
#include "lib/include/thread/threadmanager.h"

namespace TestNet
{
	class CallBack : public MsgCallBack
	{
	public:
		CallBack()
			: MsgCallBack(){}
		~CallBack(){}

		void	Accept(NetHandle handle, const char *ip){}

	    void	Recv(GameMsg *msg){}

		void	Disconnect(NetHandle handle, int err, int reason){}
	};

	void Test1()
	{
		ThreadManager thread_manager;
		NetManager *net_manager = new NetManager(&thread_manager);
		for(int i = 0; i < 10000; ++i)
		{
			if (net_manager->SyncConnect("127.0.0.1", 12347, new CallBack()) == -1)
			{
				printf("can not connect server %d\n", i);
				break;
			}
			Time::Sleep(2);
		}
		printf("test end ...\n");
	}

	void Test2()
	{
		char buf[8];
		ThreadManager thread_manager;
		NetManager *net_manager = new NetManager(&thread_manager);
		for (int i = 0; i < 100; ++i)
		{
			NetHandle handle = net_manager->SyncConnect("127.0.0.1", 12347, new CallBack());
			if (handle == -1)
			{
				printf("can not connect server %d\n", i);
				break;
			}
			Time::Sleep(2);
			(*(int *)buf) = rand() % 20000 - 10000;
			net_manager->Send(handle, 8, buf);
		}
		printf("test end ...\n");
	}
}

#endif