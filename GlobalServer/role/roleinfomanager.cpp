
#include "roleinfomanager.h"

RoleInfoManager::RoleInfoManager()
	:m_all_role_info(2048)
{

}

RoleInfoManager::~RoleInfoManager()
{
	ALL_ROLE_INFO::iterator itr = m_all_role_info.Begin();
	for (; itr != m_all_role_info.End(); ++itr)
	{
		delete (*itr);
	}
}


void RoleInfoManager::OnRoleLogin()
{
	/* 
		玩家登录，如果没有加载过其关系角色信息，加载信息:
		* 自己的信息
		* 帮派成员
		* 好友列表
		* ...
	*/

	// 遍历所有关系角色，调用checkRoleInfoEx
	// 最后冲刷
	flush();
}

// 当每个功能需要用到离线数据时，可以在启动时调用此接口
// 排行的全部玩家信息加载到内存
void RoleInfoManager::checkRoleInfo(RoleID role_id)
{
	ALL_ROLE_INFO::iterator itr = m_all_role_info.Find(role_id);
	if (itr == m_all_role_info.End())
	{
		// 到数据库去查找
	}
}
// 主要用列表查询，统一到数据库查找，减少查询次数
void RoleInfoManager::checkRoleInfoEx(RoleID role_id)
{
	ALL_ROLE_INFO::iterator itr = m_all_role_info.Find(role_id);
	if (itr == m_all_role_info.End())
	{
		// 加到列表
	}
}

// 冲刷查询列表
void RoleInfoManager::flush()
{

}

const RoleInfo * RoleInfoManager::FindRoleInfo(RoleID role_id)
{
	ALL_ROLE_INFO::iterator itr = m_all_role_info.Find(role_id);
	if (itr == m_all_role_info.End())
	{
		return NULL;
	}
	return *itr;
}

