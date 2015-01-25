
#ifndef HASHLISTTEST_H
#define HASHLISTTEST_H

#include "common/datastructure/hashlist.h"

namespace HashListTest
{
	void StrHashListTest()
	{
		StrHashList<int> test;
		int a = 1;
		test.Push("a", a);
		a = 2;
		test.Push("b", a);
		printf("%d\n", *test["a"]);
	}
}

#endif // !HASHLISTTEST_H
