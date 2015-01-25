
#ifndef TESTCACHE_H
#define TESTCACHE_H

#include "cache/datacache.h"

class TestCache
{
public:
	TestCache();
	~TestCache(){};

	enum CacheField
	{
		ROLE_ID,
		ROLE_NAME,
		GOLD,
		COIN
	};
private:
	DataCache m_cache;
};

#endif