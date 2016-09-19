
#ifndef GAME_GLOBAL_H
#define GAME_GLOBAL_H

#include "lib/include/thread/basethread.h"
#include "common/datastructure/gamevector.h"


class Role;
class ThreadManager;
class Global : public BaseThread
{
public:
	Global(ThreadManager *thread_manager);
	~Global();

protected:
	bool	Init();
	bool	Run();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);

private:
	
	game::Vector<Role *> m_role_manager;

};


#endif // !GAME_GLOBAL_H
