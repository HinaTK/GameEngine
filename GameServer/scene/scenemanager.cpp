
#include "scenemanager.h"

SceneManager::SceneManager(ThreadManager *thread_manager)
: BaseThread(thread_manager)
{
	m_name = "scene";
}

SceneManager::~SceneManager()
{

}

bool SceneManager::Init()
{
	return true;
}

bool SceneManager::Run()
{
	return false;
}

void SceneManager::RecvData(short type, ThreadID sid, int len, const char *data)
{

}
