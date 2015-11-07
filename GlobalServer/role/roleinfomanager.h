
#ifndef ROLE_INFO_MANAGER_H
#define ROLE_INFO_MANAGER_H

#include "roleinfo.h"
#include "common/commonvariable.h"
#include "common/datastructure/gamehash.h"

/*
	* 主要用显示玩家信息(支持离线)
	* 之后考虑移植到globalserver
	* 玩家登录

*/

class RoleInfoManager
{
public:
	~RoleInfoManager();

	static RoleInfoManager &Instance()
	{
		static RoleInfoManager rim;
		return rim;
	};

	void	OnRoleLogin();
	void	checkRoleInfo(RoleID role_id);
	void	checkRoleInfoEx(RoleID role_id);
	void	flush();

	void	AddRoleInfo(RoleID role_id, RoleInfo *info);
	
	// 玩家在线，需要更新其信息（如果写在gameserver,直接可以取得玩家信息，因此不需要实时更新，只需要在玩家下线时，更新一下）
	// void	UpdateRoleInfo(RoleID role_)

	const RoleInfo *FindRoleInfo(RoleID);

private:
	RoleInfoManager();
	typedef game::Hash<RoleID, RoleInfo *> ALL_ROLE_INFO;
	ALL_ROLE_INFO	m_all_role_info;

};

#endif