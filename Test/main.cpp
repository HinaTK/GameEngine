
#include <stdio.h>
#include <string>
#include "testdatastructure.h"
#include "testlog.h"
#include "testserializer.h"
#include "testmemory.h"
#include "testother.h"
#include "testcache.h"
#include "testthread.h"
#include "testframe.h"
#include "testredis.h"
#include "testchrono.h"
#include "lib/include/thread/threadmanager.h"

class A
{
public:

	virtual void Show()
	{
		printf("class A\n");
	}
};

class B : public A
{
public:

	void Show()
	{
		A::Show();
		printf("class B\n");
	}
};

int main()
{
// 	A *a = new B;
// 	a->Show();
// 	delete a;
	//printf("%s\n", Function::WorkDir().c_str());
	//VariableSave();
	// WebSocketTest::Listen();
	//ThreadTest::MutexTest();
	//HashListTest::StrHashListTest();
	//Function::WindowsPause();
	//SocketTest::Connect();
	//SocketTest::Connect1();
	//MemoryTest::MallocTest();
	//LogTest::Test();
	//LogTest::MakeDir();
	//CircleQueueTest::Test();
// 	{
// 		Computer computer;
// 		{
// 			CPU cpu = computer.GetCPU1();
// 		}
// 	}

// 	{
// 		Computer computer;
// 		{
// 			CPU *cpu = computer.GetCPU2();
// 		}
// 	}
//	ThreadTest::CreateThread();
	//TestDataStructure::TestGameSet();

	//TestLog::WriteLog();
	//TestSerializer::Normal();
	//TestSerializer::ShowLength();
	//TestSerializer::NormalDB();
	//TestMemory::TestMemoryVL();
	//TestMemory::Test1();
	//TestSocket::Connect();

	//TestDataStructure::TestArray();
	//TestDataStructure::TestArrayCmpMap();
	//TestDataStructure::TestVector();
	//TestDataStructure::TestVector2();
	//TestDataStructure::TestVector3();
	//TestDataStructure::TestRankList();
	//TestDataStructure::TestSortMap2();
	//TestDataStructure::TestGameMap();
	//TestDataStructure::TestGameMapCmpMap();
	//TestDataStructure::TestList();
	//TestDataStructure::TestList2();
	//TestDataStructure::TestList3();
	//TestDataStructure::TestHash();
	
	//TestDataStructure::TestMsgQueue2();
	//TestOther::Test1();
	//TestOther::Test2();
	//TestOther::Test3();
	//TestOther::Test4();

	//TestCache::TestDataQueue();
	//TestCache::TestDataMap();
	//TestCache::TestDataCache();
	//TestCache::TestCache1();
	//TestThread::Test1();
	//TestThread::Test2();

	//TestRedis::Test1();
	//TestRedis::Test2();
	//TestRedis::Test3();
	//TestRedis::Test4();
	//TestRedis::Test5();

	//TestChrono::Test1();
	//TestChrono::Test2();
	//TestChrono::Test3();

//	TestFrame::Instance().Init();
//	TestFrame::Instance().Run();

// 	struct S1
// 	{
// 		char	a;
// 		int		b;
// 		double	c;
// 	};
// 
// 	struct S2
// 	{
// 		char	a;
// 		double	b;
// 		int		c;
// 		double	d;
// 	};
// 
// 	printf("S1 = %d\n", sizeof(S1));
// 	printf("S2 = %d\n", sizeof(S2));
	ThreadManager thread_manager;
	thread_manager.Register(ThreadManager::ID_MAIN, new TestThread2(&thread_manager));

	thread_manager.Start();
	bool is_run = true;
	while (is_run)
	{
		char cmd_buf[512] = { 0 };
		gets(cmd_buf);
		if (strncmp(cmd_buf, "exit", 4) == 0)
		{
			break;
		}
		else if (strncmp(cmd_buf, "test", 4) == 0)
		{
			for (int i = 0; i < 1000001; ++i)
			{
				ThreadMsg *msg = new ThreadMsg(sizeof(int), (const char *)&i);
				thread_manager.SendMsg(ThreadManager::ID_MAIN, msg);
				// 				ThreadMsg *msg2 = new ThreadMsg(sizeof(int), (const char *)&i);
				// 				m_thread_manager.PushMsg(ThreadManager::ID_DB, msg2);
			}
			printf("ttttttttttttttt \n");
		}
		//		printf("%s\n", cmd_buf);
	}
	thread_manager.Exit();
	thread_manager.Wait();
	return 0;
}

