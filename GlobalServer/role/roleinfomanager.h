
#ifndef ROLE_INFO_MANAGER_H
#define ROLE_INFO_MANAGER_H

#include "roleinfo.h"
#include "common/commonvariable.h"
#include "common/datastructure/gamehash.h"

/*
	* ��Ҫ����ʾ�����Ϣ(֧������)
	* ֮������ֲ��globalserver
	* ��ҵ�¼

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
	
	// ������ߣ���Ҫ��������Ϣ�����д��gameserver,ֱ�ӿ���ȡ�������Ϣ����˲���Ҫʵʱ���£�ֻ��Ҫ���������ʱ������һ�£�
	// void	UpdateRoleInfo(RoleID role_)

	const RoleInfo *FindRoleInfo(RoleID);

private:
	RoleInfoManager();
	typedef game::Hash<RoleID, RoleInfo *> ALL_ROLE_INFO;
	ALL_ROLE_INFO	m_all_role_info;

};

#endif