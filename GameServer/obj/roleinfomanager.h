
#ifndef ROLE_INFO_MANAGER_H
#define ROLE_INFO_MANAGER_H

#include "roleinfo.h"
#include "common/commonvariable.h"
#include "common/datastructure/gamehash.h"

/*
	��Ҫ����ʾ�����Ϣ(֧������)
	֮������ֲ��globalserver
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

	// ��ʼ������"�����Ծ����б�"��hash�б�
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