
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
	bool	EnterScene(SceneID scene_id, ObjID obj_id, int x, int y);
	ObjID	CreateRole();
private:
	typedef std::map<SceneID, Scene * > SCENE_MAP;
	typedef game::Array<Obj *>			ROLE_ARRAY;

	SCENE_MAP	m_scene_map;
	ROLE_ARRAY	m_role_array;

};

#endif