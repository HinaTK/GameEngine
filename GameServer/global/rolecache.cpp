
#include "rolecache.h"
#include "scene/obj/role.h"

/*
	判断索引的作用是：玩家多次上下线，之前保存在列表前面的数据不能准确描述最近最少使用算法（LRU）
*/

RoleCache::RoleCache()
: m_index(0)
{

}

void RoleCache::Push(Role *role)
{
	RoleID rid = role->GetID();
	ROLE_HASH::iterator itr = m_role_hash.Find(rid);
	if (itr != m_role_hash.End())
	{
		return;
	}

	m_role_hash.Push(rid, RoleHash{role, m_index});
	m_role_list.push_back(RoleList{rid, m_index});
	++m_index;
	if (m_role_list.size() > MAX_ROLE_NUM)
	{
		RoleList info = m_role_list.front();
		m_role_list.pop_front();
		ROLE_HASH::iterator itr2 = m_role_hash.Find(info.rid);
		if (itr2 != m_role_hash.End())
		{
			if (itr2->index == info.index)
			{
				m_role_hash.Erase(info.rid);
				delete itr2->role;
			}
		}
	}
}

Role * RoleCache::Pop(RoleID rid)
{
	ROLE_HASH::iterator itr = m_role_hash.Find(rid);
	if (itr != m_role_hash.End())
	{
		m_role_hash.Erase(rid);
		return itr->role;
	}

	return NULL;
}