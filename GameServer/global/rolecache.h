
#ifndef ROLE_CACHE_H
#define ROLE_CACHE_H

#include <list>
#include "common/datastructure/gamehash.h"

class Role;
class RoleCache
{
public:
	RoleCache();
	static const int MAX_ROLE_NUM = 1024;
	void	Push(Role *role);

	Role *	Pop(RoleID rid);
private:
	struct RoleHash
	{
		Role *role;
		unsigned int index;
	};

	struct RoleList
	{
		RoleID rid;
		unsigned int index;
	};
	
	typedef game::Hash<RoleID, RoleHash> ROLE_HASH;
	typedef std::list<RoleList> ROLE_LIST;

	ROLE_HASH 	m_role_hash;
	ROLE_LIST	m_role_list;
	unsigned int m_index;
};

#endif