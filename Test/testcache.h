
#ifndef TEST_CACHE_H
#define TEST_CACHE_H

#include "lib/include/cache/datamap.h"
#include "lib/include/cache/datacache.h"

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

	void TestDataCache()
	{
		

		enum CacheField
		{
			ROLE_ID,
			ROLE_NAME,
			GOLD,
			COIN,
			MAX_FIELD
		};

		DataCache<int> cache(MAX_FIELD);
		cache.FieldDefine(ROLE_ID,		DT_INT, 4);
		cache.FieldDefine(ROLE_NAME,	DT_STR, 32);
		cache.FieldDefine(GOLD,			DT_INT, 4);
		cache.FieldDefine(COIN,			DT_INT, 4);

		DataList list;
		FieldData data;
		data.field = ROLE_ID;
		data.value.dv_int = 789;
		list.Push(data);
		int key = 123;
		cache.Update(key, list);
		DataList list2;
		cache.Find(key, list2);
	}

	void TestCache1()
	{
//		DataMap<int> test;
//		unsigned long begin = GetTickCount();
//		int test_num = 100000;
//		for (int i = 0; i < test_num; ++i)
//		{
//			test.Insert(i, (const char *)&i, sizeof(int));
//		}
//		printf("time = %d\n", GetTickCount() - begin);
	}

}

#endif
