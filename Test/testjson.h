
#ifndef TEST_JSON_H
#define TEST_JSON_H

#include "lib/include/json/json.h"

namespace TestJson
{
	void Test1()
	{
		Json::Value test;
		test[0] = 'v';
		test[1] = 123;
		test[2] = "jia";
		std::string ret = test.toStyledString();
	}

	void Test2()
	{
		Json::Value root;

		for (int i = 0; i < 3; ++i)
		{
			Json::Value test;
			test[0] = 'v';
			test[1] = 123;
			test[2] = "jia";

			root[i] = test;
		}
		
		std::string ret = root.toStyledString();
	}

	void Test3()
	{
		struct Item
		{
			int id = 0;
			int level = 1;
		};

		struct Data
		{
			int item_id = 0;
			int item_num = 0;
			std::vector<int> item_list;
			std::vector<Item> item_list2;
		};

	}
}


#endif // !TEST_JSON_H
