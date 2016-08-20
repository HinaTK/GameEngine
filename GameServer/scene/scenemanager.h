
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "lib/include/thread/basethread.h"

class ThreadManager;
class SceneManager : public BaseThread
{
public:
	SceneManager(ThreadManager *thread_manager);
	~SceneManager();

protected:
	bool	Init();
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);

private:
};

#endif