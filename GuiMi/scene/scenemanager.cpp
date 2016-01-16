
#include "scenemanager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

bool SceneManager::Init(int map_id, int map_w, int max_h)
{
	// 暂时将map_id 当 scene_id用
	Scene *scene = new Scene(map_id, this);
	m_scene_map[map_id] = scene;
	return true;
}

bool SceneManager::EnterScene(SceneID scene_id, ObjID obj_id, int x, int y)
{
	SCENE_MAP::iterator scene_itr = m_scene_map.find(scene_id);
	if (scene_itr == m_scene_map.end())
	{
		return false;
	}

	ROLE_ARRAY::iterator role_itr = m_role_array.Find(obj_id);
	if (role_itr == m_role_array.End())
	{
		return false;
	}



	return true;
}

ObjID SceneManager::CreateRole()
{
	Obj *obj = new Obj;
	return m_role_array.Insert(obj);
}
