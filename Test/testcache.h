
#ifndef TEST_CACHE_H
#define TEST_CACHE_H

#include "cache/dataqueue.h"

namespace TestCache
{
	class Test
	{
	public:
		Test(){};
		~Test(){};

		void CallBack(const char *data, unsigned int length)
		{
			printf("fuck\n");
		}
	private:

	};

	void CallBack(const char *data, unsigned int length)
	{
		printf("data = %s\n", data);
		printf("fuck\n");
	}

	void TestDataQueue()
	{
		DataQueue m_data;
		Test test;
		char *a = "jia";
		m_data.Push(a, strlen(a), CallBack);
		char *b = new char[10];
		unsigned int c = 0;
		m_data.Pop();
	}
}

#endif