
#ifndef ROLE_CACHE_H
#define ROLE_CACHE_H

#include <list>
#include "common/datastructure/gamehash.h"

class Role;
class RoleCache
{
public:
	static const int MAX_ROLE_NUM = 1024;
	void	Push(Role *role);

private:
	// todo 做一个双数据结构，因为
	typedef game::Hash<RoleID, Role *> ROLE_HASH;
	typedef std::list<RoleID> ROLE_LIST;

	ROLE_HASH 	m_role_hash;
	ROLE_LIST	m_role_list;
};

#endif