
#include "rolecache.h"
#include "scene/obj/role.h"

void RoleCache::Push(Role *role)
{
	RoleID id = role->GetID();
	ROLE_HASH::iterator itr = m_role_hash.Find(id);
	if (itr != m_role_hash.End())
	{
		return;
	}

	m_role_hash.Push(id, role);
	m_role_list.push_back(id);
	if (m_role_list.size() > MAX_ROLE_NUM)
	{
		// TODO 去除队列头
	}
}