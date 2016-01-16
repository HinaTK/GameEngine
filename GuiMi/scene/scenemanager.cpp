
#include "scenemanager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

bool SceneManager::Init(int map_id, int map_w, int max_h)
{
	// todo ��ʱ��map_id �� scene_id��
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
		// todo дlog
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

	// ��ʱ��obj ���� role,֮��Ҫ��lua����accout,��ǿ�жϣ���������������ڶ����ͬ��ɫ
	Obj *obj = new Obj;
	obj->SetScene(itr->second);
	itr->second->Enter(obj, aoi_x, aoi_y);
	return m_role_array.Insert(obj);
}

// ����
bool SceneManager::DeleteRole(RoleID role_id)
{
	ROLE_ARRAY::iterator itr = m_role_array.Find(role_id);
	if (itr == m_role_array.End())
	{
		// todo дlog
		return false;
	}

	Obj *obj = *itr;
	Scene *scene = obj->GetScene();
	
	return scene->DelObj(obj->GetObjID());
}

// �г���
bool SceneManager::RemoveRole(SceneID scene_id, RoleID role_id)
{
	SCENE_MAP::iterator itr = m_scene_map.find(scene_id);
	if (itr == m_scene_map.end())
	{
		// todo дlog
		return false;
	}

	ROLE_ARRAY::iterator role_itr = m_role_array.Find(role_id);
	if (role_itr == m_role_array.End())
	{
		// todo дlog
		return false;
	}

	return itr->second->DelObj((*role_itr)->GetObjID());
}
