
#ifndef	ROLE_INFO_H
#define ROLE_INFO_H

#include "common/commonvariable.h"

/*
	Íæ¼ÒÐÅÏ¢
*/

class RoleInfo
{
public:
	~RoleInfo(){};
	RoleInfo()
		: m_level(0)
	{
		memset(m_role_name, 0, GAME_NAME_LEN);
	}
	

	void	SetRoleName(GameName name){ memcpy(m_role_name, name, GAME_NAME_LEN); m_role_name[GAME_NAME_LEN - 1] = 0; }
	void	GetRoleName(GameName name){ memcpy(name, m_role_name, GAME_NAME_LEN); }
	int		m_level;

private:
	GameName	m_role_name;
};

#endif