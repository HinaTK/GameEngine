
#ifndef SCENE_H
#define SCENE_H

#include "areamanager.h"
#include "obj/objmanager.h"

class SceneManager;
class Scene
{
public:
	Scene(SceneID scene_id, SceneManager *scene_manager);
	~Scene();

	enum SCENE_TYPE
	{
		ST_COMMON = 0,	// ∆’Õ®≥°æ∞
	};

	bool		Init(int map_w, int map_h, int area_x, int area_y);
	bool		DelObj(ObjID obj_id);

	bool		Enter(Obj *obj, int aoi_x, int aoi_y);

	SceneID		GetSceneID(){ return m_scene_id; }

	void *	operator new(size_t c);
	void	operator delete(void *m);
private:
	SceneManager	*m_scene_manager;
	AreaManager		m_area_manager;
	ObjManager		m_obj_manager;

	SceneID			m_scene_id;
};

#endif