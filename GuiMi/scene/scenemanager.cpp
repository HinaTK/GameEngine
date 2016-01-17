
#include "scenemanager.h"
#include "obj/role.h"

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

bool SceneManager::ChangeScene(SceneID scene_id, ObjID obj_id, int x, int y, int aoi_x, int aoi_y, SceneRet &ret)
{
	SCENE_MAP::iterator scene_itr = m_scene_map.find(scene_id);
	if (scene_itr == m_scene_map.end())
	{
		return false;
	}

	OBJ_MANAGER::iterator itr = m_obj_manager.Find(obj_id);
	if (itr == m_obj_manager.End())
	{
		// todo 写log
		return false;
	}

	Obj *obj = *itr;
	obj->SetPos(Posi(x, y));

	Scene *old_scene = obj->GetScene();
	Scene *scene = scene_itr->second;

	if (old_scene != NULL)
	{
		// todo leave scene
		old_scene->Leave(obj_id, ret);
	}

	if (obj == scene->GetObj(obj->GetObjID()))
	{
		// todo 切坐标，改变aoi
	}
	else
	{
		obj->SetScene(scene);
		scene->Enter(obj, aoi_x, aoi_y, ret);
	}

	return true;
}

ObjID SceneManager::CreateRole()
{
	Role *role = new Role();
	return m_obj_manager.Insert(role);
}

// 下线
bool SceneManager::DeleteRole(ObjID obj_id)
{
	OBJ_MANAGER::iterator itr = m_obj_manager.Find(obj_id);
	if (itr == m_obj_manager.End())
	{
		// todo 写log
		return false;
	}

	Obj *obj = *itr;
	Scene *scene = obj->GetScene();
	
	return scene->DelObj(obj->GetObjID());
}

// 切场景
bool SceneManager::RemoveRole(SceneID scene_id, ObjID obj_id)
{
	SCENE_MAP::iterator itr = m_scene_map.find(scene_id);
	if (itr == m_scene_map.end())
	{
		// todo 写log
		return false;
	}

	OBJ_MANAGER::iterator role_itr = m_obj_manager.Find(obj_id);
	if (role_itr == m_obj_manager.End())
	{
		// todo 写log
		return false;
	}

	return itr->second->DelObj((*role_itr)->GetObjID());
}
