
#include "testcache.h"

TestCache::TestCache()
{
	//m_cache.m_fields.push_back()

	m_cache.FieldDefine( ROLE_ID,		DT_INT, 4);
	m_cache.FieldDefine( ROLE_NAME,		DT_STR, 32);
	m_cache.FieldDefine( GOLD,			DT_INT, 4);
	m_cache.FieldDefine( COIN,			DT_INT, 4);
}
