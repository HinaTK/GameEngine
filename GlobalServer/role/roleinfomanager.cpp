
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
		��ҵ�¼�����û�м��ع����ϵ��ɫ��Ϣ��������Ϣ:
		* �Լ�����Ϣ
		* ���ɳ�Ա
		* �����б�
		* ...
	*/

	// �������й�ϵ��ɫ������checkRoleInfoEx
	// ����ˢ
	flush();
}

// ��ÿ��������Ҫ�õ���������ʱ������������ʱ���ô˽ӿ�
// ���е�ȫ�������Ϣ���ص��ڴ�
void RoleInfoManager::checkRoleInfo(RoleID role_id)
{
	ALL_ROLE_INFO::iterator itr = m_all_role_info.Find(role_id);
	if (itr == m_all_role_info.End())
	{
		// �����ݿ�ȥ����
	}
}
// ��Ҫ���б��ѯ��ͳһ�����ݿ���ң����ٲ�ѯ����
void RoleInfoManager::checkRoleInfoEx(RoleID role_id)
{
	ALL_ROLE_INFO::iterator itr = m_all_role_info.Find(role_id);
	if (itr == m_all_role_info.End())
	{
		// �ӵ��б�
	}
}

// ��ˢ��ѯ�б�
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

