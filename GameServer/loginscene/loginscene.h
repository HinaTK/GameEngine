
#ifndef LOGIN_SCENE_H
#define LOGIN_SCENE_H

#include "lib/include/thread/basethread.h"
#include "common/datastructure/gamevector.h"

/*
	在登录之前，玩家的数据都发到这里
*/

class ThreadManager;
class Role;
class LoginScene : public BaseThread
{
public:
	LoginScene(ThreadManager *thread_manager);
	~LoginScene();

protected:
	bool	Init();
	bool	Run();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);

private:
	game::Vector<Role *> m_role_manager;
};

#endif