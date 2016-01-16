
#include "scenemanager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

bool SceneManager::Init(int map_id, int map_w, int max_h)
{
	// todo 暂时将map_id 当 scene_id用
	Scene *scene = new Scene(map_id, this);
	m_scene_map[map_id] = scene;
	return true;
}

bool SceneManager::EnterScene(SceneID scene_id, RoleID role_id, int x, int y, int aoi_x, int aoi_y)
{
	SCENE_MAP::iterator scene_itr = m_scene_map.find(scene_id);
	if (scene_itr == m_scene_map.end())
	{
		return false;
	}

	ROLE_ARRAY::iterator itr = m_role_array.Find(role_id);
	if (itr == m_role_array.End())
	{
		// todo 写log
		return false;
	}

	Obj *obj = *itr;
	obj->SetPos(Posi(x, y));
	scene_itr->second->Enter(obj, aoi_x, aoi_y);
	return true;
}

RoleID SceneManager::CreateRole(SceneID scene_id, int aoi_x, int aoi_y)
{
	SCENE_MAP::iterator itr = m_scene_map.find(scene_id);
	if (itr == m_scene_map.end())
	{
		return 0;
	}

	// 暂时用obj 代替 role,之后要从lua传入accout,加强判断，避免出错，场景存在多个相同角色
	Obj *obj = new Obj;
	obj->SetScene(itr->second);
	itr->second->Enter(obj, aoi_x, aoi_y);
	return m_role_array.Insert(obj);
}

// 下线
bool SceneManager::DeleteRole(RoleID role_id)
{
	ROLE_ARRAY::iterator itr = m_role_array.Find(role_id);
	if (itr == m_role_array.End())
	{
		// todo 写log
		return false;
	}

	Obj *obj = *itr;
	Scene *scene = obj->GetScene();
	
	return scene->DelObj(obj->GetObjID());
}

// 切场景
bool SceneManager::RemoveRole(SceneID scene_id, RoleID role_id)
{
	SCENE_MAP::iterator itr = m_scene_map.find(scene_id);
	if (itr == m_scene_map.end())
	{
		// todo 写log
		return false;
	}

	ROLE_ARRAY::iterator role_itr = m_role_array.Find(role_id);
	if (role_itr == m_role_array.End())
	{
		// todo 写log
		return false;
	}

	return itr->second->DelObj((*role_itr)->GetObjID());
}
