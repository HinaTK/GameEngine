
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include "define.h"
#include "scene.h"
#include "common/datastructure/gamevector.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

private:
	typedef std::map<SceneID, Scene * > SCENE_MAP;
	typedef game::Array<Obj *>			OBJ_MANAGER;

public:
	bool	Init(int map_id, int map_w, int max_h);

	bool	AddScene(Scene *scene){ m_scene_map[scene->GetSceneID()] = scene; return true; }
	bool	ChangeScene(SceneID scene_id, ObjID obj_id, int x, int y, int aoi_x, int aoi_y, SceneRet &ret);
	ObjID	CreateRole();
	bool	DeleteRole(ObjID role_id);
	bool	RemoveRole(SceneID scene_id, ObjID obj_id);

	OBJ_MANAGER *GetObjManager(){ return &m_obj_manager; }
private:

	SCENE_MAP	m_scene_map;
	OBJ_MANAGER	m_obj_manager;
};

#endif