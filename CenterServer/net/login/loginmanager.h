
#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <map>
#include "common/serverdef.h"

class NetThread;
class LoginManager
{
public:
	LoginManager(NetThread *t);
	~LoginManager();

	
	void 	OnLogin(Account account, ServerID server_id);
	// struct LoginKey
	// {
	// 	Account 	account;
	// 	ServerID	server_id;
	// };

	// struct LoginInfo
	// {
	// 	RoleID		role_id;
	// 	RoleName	role_name;
	// };
protected:
	NetThread	*m_thread;
	//std::map<LoginKey, LoginInfo> m_login_info;
};

#endif