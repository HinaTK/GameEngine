
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

void RoleInfoManager::Init()
{

}

// 当每个功能需要用到离线数据时，启动是需要调用此接口
void RoleInfoManager::checkRoleInfo(RoleID role_id)
{
	ALL_ROLE_INFO::iterator itr = m_all_role_info.Find(role_id);
	if (itr == m_all_role_info.End())
	{
		// 到数据库去查找
	}
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

