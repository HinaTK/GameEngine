
#ifndef GAME_GLOBAL_H
#define GAME_GLOBAL_H

#include "rolecache.h"
#include "lib/include/thread/basethread.h"
#include "common/datastructure/gamevector.h"


class TempRole;
class ThreadManager;
class Global : public BaseThread
{
public:
	Global(ThreadManager *thread_manager);
	~Global();

protected:
	void	RoleLogin(RoleID rid);
	void	RoleLogout(Role *role);
protected:
	bool	Init();
	bool	Run();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);

private:
	
	game::Vector<TempRole> m_role_manager;
	RoleCache 	m_role_cache;

};


#endif // !GAME_GLOBAL_H
