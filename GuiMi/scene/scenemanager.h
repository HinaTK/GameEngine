
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include "define.h"
#include "scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool	Init(int map_id, int map_w, int max_h);

	bool	AddScene(Scene *scene){ m_scene_map[scene->GetSceneID()] = scene; return true; }
	bool	EnterScene(SceneID scene_id, RoleID role_id, int x, int y, int aoi_x, int aoi_y);
	RoleID	CreateRole(SceneID scene_id, int aoi_x, int aoi_y);
	bool	DeleteRole(RoleID role_id);
	bool	RemoveRole(SceneID scene_id, RoleID role_id);

private:
	typedef std::map<SceneID, Scene * > SCENE_MAP;
	typedef game::Array<Obj *>			ROLE_ARRAY;

	SCENE_MAP	m_scene_map;
	ROLE_ARRAY	m_role_array;
};

#endif