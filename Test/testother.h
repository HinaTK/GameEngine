
#ifndef TEST_OTHER_H
#define TEST_OTHER_H

#include "timemanager/gametime.h"
#include "DLL/export.h"
#include "DLL/dll.h"

class TTTT
{
public:

	DLL *m_dll;
};

namespace TestOther
{
// 	void Test1()
// 	{
// 		int test_time = 1000000;
// 		static const int length = 130;
// 		char data[length];
// 		char mask_data[4];
// 		printf("%d\n", GameTime::MilliSecond());
// 		for (int t = 0; t < test_time; ++t)
// 		{
// 			for (int i = 0; i < length; ++i)
// 			{
// 				data[i] = (data[i] ^ mask_data[i % 4]);
// 			}
// 		}	
// 		printf("%d\n", GameTime::MilliSecond());
// 		for (int t = 0; t < test_time; ++t)
// 		{
// 			int size = length - (length % 4);
// 			for (int i = 0; i < size; i = i + 4)
// 			{
// 				data[i] = (data[i] ^ mask_data[0]);
// 				data[i + 1] = (data[i + 1] ^ mask_data[1]);
// 				data[i + 2] = (data[i + 2] ^ mask_data[2]);
// 				data[i + 3] = (data[i + 3] ^ mask_data[3]);
// 			}
// 			for (int i = size; i < length; ++i)
// 			{
// 				data[i] = (data[i] ^ mask_data[i - size]);
// 			}
// 		}
// 		printf("%d\n", GameTime::MilliSecond());
// 	}
// 
// 	void Test2()
// 	{
// 		int test_time = 20000000;
// 		int times = 123;
// 
// 		printf("%lld\n", GameTime::MilliSecond());
// 		for (int t = 0; t < test_time; ++t)
// 		{
// 			int temp = times * 1000;
// 		}
// 		printf("%lld\n", GameTime::MilliSecond());
// 		for (int t = 0; t < test_time; ++t)
// 		{
// 			int temp = (times << 10) - (times << 4) - (times << 3);
// 		}
// 		printf("%lld\n", GameTime::MilliSecond());
// 	}

	void Test3()
	{
		Register();
	}

	void Test4()
	{
		Test test;
		Register(test);
	}
}

#endif