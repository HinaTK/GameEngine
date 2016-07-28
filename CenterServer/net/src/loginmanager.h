
#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <map>
#include "proto.h"
#include "common/serverdef.h"

class NetThread;
class LoginManager
{
public:
	LoginManager(NetThread *t);
	~LoginManager();

	
	void 	OnLogin(Proto::csLogin *login);
	void 	OnCreateRole(Proto::csCreateRole *role);
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