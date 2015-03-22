
#ifndef TEST_CACHE_H
#define TEST_CACHE_H

#include "cache/dataqueue.h"
#include "cache/datamap.h"

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
// 		DataQueue m_data;
// 		Test test;
// 		char *a = "jia";
// 		m_data.Push(a, strlen(a), CallBack);
// 		char *b = new char[10];
// 		unsigned int c = 0;
// 		m_data.Pop();
	}

	void TestDataMap()
	{
// 		struct Key
// 		{
// 			int id;
// 			int type;
// 
// 			bool operator!=(Key &k)
// 			{
// 				return (id != k.id || type != k.type);
// 			}
// 
// 			bool operator<(Key &k)
// 			{
// 				return (id < k.id && type < k.type);
// 			}
// 		};
// 		DataMap<Key> m_data;
// 
// 		Key key1;
// 		Key key2;
// 		key1.id = 1;
// 		key1.type = 23;
// 		key2.id = 1;
// 		key2.type = 12;
// 		
// 		char *data1 = "jia\n";
// 		char *data2 = "ming\n";
// 		unsigned int length = 10;
// 		m_data.Insert(key1, data1, length);
// 		m_data.Insert(key2, data2, length);
// 
// 		const char *data = NULL;
// 		m_data.Find(key2, &data, length);
	}

}

#endif