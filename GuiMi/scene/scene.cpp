
#include "scene.h"


Scene::~Scene()
{

}

Scene::Scene(SceneID scene_id, SceneManager *scene_manager)
: m_scene_id(scene_id)
, m_scene_manager(scene_manager)
, m_area_manager(&m_obj_manager)
{

}

bool Scene::Init(int map_w, int map_h, int area_x, int area_y)
{
	m_area_manager.Init(area_x, area_y, map_w, map_h);
	AreaManager::CreateAreaMatrix(&m_area_manager, area_x, area_y, map_w, map_h);
	return true;
}

bool Scene::DelObj(ObjID obj_id)
{
	return m_obj_manager.Del(obj_id);
}

bool Scene::Enter(Obj *obj, int aoi_x, int aoi_y)
{
	ObjID obj_id = m_obj_manager.Add(obj);
	obj->SetObjID(obj_id);
	m_area_manager.CreateRectAOI(obj_id, obj->GetPos(), aoi_x, aoi_y);
	return true;
}