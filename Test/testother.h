
#ifndef TEST_OTHER_H
#define TEST_OTHER_H

//#include "lib/include/timemanager/gametime.h"
#include "lib/include/base/interface.h"
#include "lib/include/base/gametime.h"


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

//	void Test3()
//	{
//		Register();
//	}

//	void Test4()
//	{
//		Test test;
//		Register(test);
//	}

	void Test5()
	{
		GameTime *test = (GameTime *)Time::NewGameTime();
		printf("vvvvvvvvvvvvv %d\n", test->Start());
		delete test;
	}

	void Test6()
	{
		unsigned char jjj[] = "jiaming";
		unsigned char kkk[64] = { 0 };
		unsigned char lll[64] = { 0 };
		Base::encrypt128(jjj, kkk);

		Base::decrypt128(kkk, lll);
	}

	void Test7()
	{
		std::string str = "jiaming";
		std::string ret = Base::MD5Encrypt(str);

		ret = Base::MD5Encrypt((const unsigned char *)"jiaming", strlen("jiaming"));
	}
}

#endif
