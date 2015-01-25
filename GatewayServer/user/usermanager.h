#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <map>
#include "../../common/commonvariable.h"

class UserManager
{
public:
	~UserManager()
	static UserManager & Instance()
	{
		static UserManager manager;
		return manager;
	}
private:
	UserManager();
private:
	std::map<RoleID,NetID> m_user_map;
};


#endif