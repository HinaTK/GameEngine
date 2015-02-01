
#ifndef TEST_DATASTRUCTURE_H
#define TEST_DATASTRUCTURE_H

#include <time.h>
#include <string>
#include <set>
#include <map>
#include <list>
#include "common/datastructure/circlequeue.h"
#include "common/datastructure/gameset.h"
#include "common/datastructure/gamemap.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/sortmap.h"
#include "common/datastructure/gamelist.h"
#include "common/datastructure/gamehash.h"
#include "timemanager/gametime.h"

namespace TestDataStructure
{
/***************************** 循环队列 *******************************/
	CircleQueue<std::string> test;
	std::string strtest;
	void Push()
	{
		std::string temp = "123";
		test.Push(temp);
		memcpy(&strtest, &temp, sizeof(std::string));
	}
	void Test()
	{
		Push();
		printf("%s\n", test.Val()->c_str());
		std::string temp1 = "456";
		test.Push(temp1);
	}

/****************************** 红黑树 *********************************/

	void CmpSetInsert()
	{
// 		static const int MAX_TEST = 1000000;
// 		std::set<int> set_test;
// 		RBTree<int> test;
// 		time_t t1 = time(NULL);
// 		for (int i = 0; i < MAX_TEST; ++i)
// 		{
// 			set_test.insert(i);
// 		}
// 		time_t t2 = time(NULL);
// 		printf("t1 = %d,t2 = %d\n", (unsigned int)t1, (unsigned int)t2);
// 		for (int i = 0; i < MAX_TEST; ++i)
// 		{
// 			test.insert(i);
// 		}
// 		time_t t3 = time(NULL);
// 		printf("t1 = %d,t3 = %d\n", (unsigned int)t1, (unsigned int)t3);
		//system("pause");
	}

	void CmpSetErase()
	{
// 		static const int MAX_TEST = 500000;
// 		std::set<int> set_test;
// 		RBTree<int> test;
// 		for (int i = 0; i < MAX_TEST; ++i)
// 		{
// 			//set_test.insert(i);
// 			test.insert(i);
// 		}
// 		time_t t1 = time(NULL);
// 		for (int i = 0; i < MAX_TEST; ++i)
// 		{
// 			//set_test.erase(i);
// 			test.erase(i);
// 		}
// 		time_t t2 = time(NULL);
// 		printf("t1 = %d,t2 = %d\n", (unsigned int)t1, (unsigned int)t2);
	}

	void TestGameSet()
	{
		static const int MAX_TEST = 4000000;
		GameSet<int> game_set;
		
		for (int i = 0; i < MAX_TEST; ++i)
		{
			//int val = rand() % 1000;
			game_set.Insert(i);
			//printf("input = %d\n", val);
		}
		time_t t1 = time(NULL);
		for (GameSet<int>::iterator itr = game_set.Begin(); itr != game_set.End(); game_set.NextNode(&itr))
		{
			//
			if (itr->key > MAX_TEST - 10)
			{
				printf("result = %d\n", itr->key);
			}
			
		}
		time_t t2 = time(NULL);
		printf("t1 = %d,t2 = %d\n", (unsigned int)t1, (unsigned int)t2);
	}

	void TestGameMap()
	{
// 		GameMap<int, int> game_map;
// 		int k = 1; int v = 11;
// 		game_map.Insert(k, v);
// 		k = 2; v = 22;
// 		game_map.Insert(k, v);
// 		k = 3; v = 33;
// 		game_map.Insert(k, v);
// 		k = 4; v = 44;
// 		game_map.Insert(k, v);
// 		for (GameMap<int, int>::iterator itr = game_map.Begin(); itr != game_map.End(); game_map.NextNode(&itr))
// 		{
// 			printf("k = %d, v = %d\n", itr->key, itr->val);
// 		}
// 		k = 3;
// 		GameMap<int, int>::iterator itr = game_map.Find(k);
// 		if (itr != game_map.End())
// 		{
// 			printf("v = %d\n", itr->val);
// 		}
// 		k = 2;
// 		game_map.Erase(k);
// 		for (GameMap<int, int>::iterator itr = game_map.Begin(); itr != game_map.End(); game_map.NextNode(&itr))
// 		{
// 			printf("k = %d, v = %d\n", itr->key, itr->val);
// 		}
	}

	void TestGameMapOnly()
	{
// 		GameMap<int, int> game_map;
// 		int k = 1; int v = 11;
// 		game_map.Insert(k, v);
// 		k = 1; v = 22;
// 		game_map.Insert(k, v);
// 		for (GameMap<int, int>::iterator itr = game_map.Begin(); itr != game_map.End(); game_map.NextNode(&itr))
// 		{
// 			printf("k = %d, v = %d\n", itr->key, itr->val);
// 		}
	}
	void TestGameMapCmpMap()
	{
		game::Map<int, int> game_map;
		std::map<int, int> _map;
		int loop_time = 50000;
		printf("%d\n", GameTime::MilliSecond());
		for (int i = 0; i < loop_time; ++i)
		{
			_map[i] = i;
		}
		for (int i = 0; i < loop_time; ++i)
		{
			_map[i] = i;
		}
		for (int i = 0; i < loop_time; ++i)
		{
			_map.erase(i);
		}
		printf("%d\n", GameTime::MilliSecond());
		for (int i = 0; i < loop_time; ++i)
		{
			game_map.Insert(i, i);
		}
		for (int i = 0; i < loop_time; ++i)
		{
			game_map.Insert(i, i);
		}
		for (int i = 0; i < loop_time; ++i)
		{
			game_map.Erase(i);
		}
		printf("%d\n", GameTime::MilliSecond());
	}

/****************************** 数组 ******************************/
	void TestArray()
	{
		game::Array<int> test;
		int a = 12;
		test.Insert(a);
		a = 34;
		test.Insert(a);
		for (game::Array<int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("%d\n", *itr);
		}
		game::Array<int>::iterator itr = test.Find(1);
		printf("%d\n", *itr);

		printf("Array Clear\n");
		test.Clear();
		for (game::Array<int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("%d\n", *itr);
		}

		a = 56;
		test.Insert(a);
		a = 78;
		test.Insert(a);
		for (game::Array<int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("%d\n", *itr);
		}

		printf("Array Erase\n");
		test.Erase(0);
		for (game::Array<int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("%d\n", *itr);
		}

	}

	void TestArrayCmpMap()
	{
		int loop_time = 100000;
		game::Array<int> game_array;
		std::map<int, int> game_map;
		printf("%d\n", GameTime::MilliSecond());
		for (int i = 0; i < loop_time; ++i)
		{
			game_map[i] = i;
		}
		for (int i = 0; i < loop_time; ++i)
		{
			game_map.erase(i);
		}
		printf("%d\n", GameTime::MilliSecond());
		for (int i = 0; i < loop_time; ++i)
		{
			game_array.Insert(i);
		}
		for (int i = 0; i < loop_time; ++i)
		{
			game_array.Erase(i);
		}
		printf("%d\n", GameTime::MilliSecond());
	}

	void TestVector()
	{
		game::Vector<int> test;
		int a = 12;
		test.Push(a);
		a = 34;
		test.Push(a);
		for (game::Vector<int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("%d\n", *itr);
		}
	}

	void TestRankList()
	{
//		RankList<int, int> test;	
//		int k = 1;int v = 23;
// 		test.Insert(k, v);
// 		k = 2; v = 23;
// 		test.Insert(k, v);
// 		k = 3; v = 13;
// 		test.Insert(k, v);
// 		k = 4; v = 203;
// 		test.Insert(k, v);
// 		k = 1; v = 123;
// 		test.Insert(k, v);
// 		k = 5; v = 2;
// 		test.Insert(k, v);
// 		k = 6; v = 65;
// 		test.Insert(k, v);
// 		k = 1; v = 1;
// 		test.Insert(k, v);
// 		k = 2; v = 32;
// 		test.Insert(k, v);
// 
// // 		for (int i = 0; i < 20; ++i)
// // 		{
// // 			int k = rand() % 15;
// // 			int v = rand() % 1000;
// // 			printf("k = %d, v = %d\n", k, v);
// // 			test.Insert(k, v);
// // 		}
// 		printf("*****************************\n");
// 		test.Show();
	}

	void TestSortMap2()
	{
		game::SortMap<int, int> test;
		int k = 1; int v = 23;
		test.Insert(k, v);
		k = 2; v = 23;
		test.Insert(k, v);
		k = 3; v = 13;
		test.Insert(k, v);
		k = 4; v = 203;
		test.Insert(k, v);
		k = 1; v = 123;
		test.Insert(k, v);
		k = 5; v = 2;
		test.Insert(k, v);
		k = 6; v = 65;
		test.Insert(k, v);
		k = 1; v = 1;
		test.Insert(k, v);
		k = 2; v = 32;
		test.Insert(k, v);
		game::SortMap<int, int>::iterator itr = test.Begin();
		for (; itr != test.End(); ++itr)
		{
			printf("%d,%d,%d\n", itr->rank, itr->first, itr->second);
		}
	}

	void TestList()
	{
		game::List<int> test;
		int a = 12;
		int b = 23;
		test.PushBack(a);
		test.PushBack(b);
		a = 34;
		test.PushFront(a);
		for (game::List<int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("%d\n", *itr);
		}
		printf("*************************\n");
		for (game::List<int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			if (*itr == 23)
			{
				test.Erase(itr);
				break;
			}
		}
		printf("*************************\n");
		for (game::List<int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("%d\n", *itr);
		}
// 		std::list<int> test2;
// 		std::list<int>::iterator itr = test2.begin();
// 		test2.erase(itr);
	}

	void TestHash()
	{
		int a = 324;

		game::Hash<int, int> test;
		test.Push(123, a);
		a = 444;
		test.Push(13, a);

		for (game::Hash<int, int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("test %d\n", *itr);
		}
		printf("*******************************\n");
		printf("test %d\n", test[123]);
		printf("*******************************\n");
		test.Erase(123);
		for (game::Hash<int, int>::iterator itr = test.Begin(); itr != test.End(); ++itr)
		{
			printf("test %d\n", *itr);
		}
		printf("*******************************\n");
// 		game::Hash<const char*, int> test2;
// 		a = 567;
// 		test2.Push("234", a);
// 		printf("%d\n", test2["234"]);
// 
// 		game::Hash<int, const char *> test3;
// 		test3.Push(a, "4567");
// 		printf("test3 %s\n", test3[a]);
// 
// 		game::Hash<const char *, const char *> test4;
// 		test4.Push("jjj", "hhhh");
// 		test4.Push("kkk", "llll");
// 
// 		printf("test4 %s\n", test4["jjj"]);

	}
}

#endif