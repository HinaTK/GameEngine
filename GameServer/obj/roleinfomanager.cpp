
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

// ��ÿ��������Ҫ�õ���������ʱ����������Ҫ���ô˽ӿ�
void RoleInfoManager::checkRoleInfo(RoleID role_id)
{
	ALL_ROLE_INFO::iterator itr = m_all_role_info.Find(role_id);
	if (itr == m_all_role_info.End())
	{
		// �����ݿ�ȥ����
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

