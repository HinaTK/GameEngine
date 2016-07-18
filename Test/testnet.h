
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
			if (net_manager->SyncConnect("192.168.0.254", 10924, new CallBack()) == -1)
			{
				printf("can not connect server %d\n", i);
				break;
			}
			Time::Sleep(8);
		}
		printf("test end ...\n");
	}
}

#endif