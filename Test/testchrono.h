
#ifndef TEST_CHRONO_H
#define TEST_CHRONO_H

#include <chrono>

namespace TestChrono
{
	void Test1()
	{
		printf("now = %lld\n", std::chrono::system_clock::now());
	}

	void Test2()
	{
		printf("1 now = %lld\n", std::chrono::system_clock::now());
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); //休眠100毫秒
		printf("2 now = %lld\n", std::chrono::system_clock::now());
	}

	void Test3()
	{
		printf("1 now = %lld\n", std::chrono::system_clock::now());
		std::this_thread::sleep_for(std::chrono::microseconds(100 * 1000)); //休眠100毫秒
		printf("2 now = %lld\n", std::chrono::system_clock::now());
	}
}

#endif