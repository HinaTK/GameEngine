
#include "scene.h"


Scene::~Scene()
{

}

Scene::Scene(SceneID scene_id, SceneManager *scene_manager)
: m_scene_id(scene_id)
, m_scene_manager(scene_manager)
{

}

bool Scene::Init(int map_w, int map_h, int area_x, int area_y)
{
	m_area_manager.Init(area_x, area_y, map_w, map_h);
	return true;
}
