
#include <stdio.h>
#include <string>
#include <stdint.h>
// #include "testdatastructure.h"
// #include "testlog.h"
// #include "testserializer.h"
// #include "testmemory.h"
 #include "testother.h"
#include "testjson.h"
// #include "testcache.h"
// #include "testredis.h"
// #include "testchrono.h"
// #include "testmongo.h"
// #include "lib/include/thread/threadmanager.h"
// #include "lib/include/math/gamemath.h"
// #include "lib/include/frame/bufmanager.h"

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

// long long RandSeed = ####;
// unsigned long Random(long max)
// {
// 	long long x;
// 	double i;
// 	unsigned long final;
// 	x = 0xffffffff;
// 	x += 1;
// 	RandSeed *= ((long long)134775813);
// 	RandSeed += 1;
// 	RandSeed = RandSeed % x;
// 	i = ((double)RandSeed) / (double)0xffffffff;
// 	final = (long)(max * i);
// 	return (unsigned long)final;
// }

int holdrand = 456;
int __cdecl rand1(void) {
	return(((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);

}

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
	//TestOther::Test5();
	//TestOther::Test6();
	//TestOther::Test7();

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

	//TestJson::Test1();
	//TestJson::Test2();
	TestJson::Test3();

//	TestFrame::Instance().Init();
//	TestFrame::Instance().Run();
//	TestMongo::Fun1();

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
// 
// 	long long m = 4294967295;
// 	long a = 214013;
// 	long c = 2531011;
// 	printf("S1 = %ld\n", (a * 11 + c) % m);
	
// 	SendBuffer *buf = new SendBuffer;
// 	delete buf;
// 	while (true)
// 	{
// 		printf("aaaaaaaaaaaaaa \n");
// 		Sleep(1000000);
// 	}
	return 0;
}

