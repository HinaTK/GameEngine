
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
	TestMemory::Test1();
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
	return 0;
}

