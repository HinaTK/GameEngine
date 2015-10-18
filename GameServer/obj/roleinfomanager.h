
#ifndef ROLE_INFO_MANAGER_H
#define ROLE_INFO_MANAGER_H

#include "roleinfo.h"
#include "common/commonvariable.h"
#include "common/datastructure/gamehash.h"

/*
	主要用显示玩家信息(支持离线)
	之后考虑移植到globalserver
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

	// 初始化加载"最近活跃玩家列表"到hash列表
	void	Init();	

	void	checkRoleInfo(RoleID role_id);

	void	AddRoleInfo(RoleID role_id, RoleInfo *info);

	const RoleInfo *FindRoleInfo(RoleID);

private:
	RoleInfoManager();
	typedef game::Hash<RoleID, RoleInfo *> ALL_ROLE_INFO;
	ALL_ROLE_INFO	m_all_role_info;

};

#endif