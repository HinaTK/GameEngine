#ifndef _AREAMANAGER_H
#define _AREAMANAGER_H

#include "global/globalvariable.h"
#include "aoi.h"
#include "area.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"

#include "observer.h"


/*
   y↑
	│
	│	┌──────┬──────┐top
	│	│			  │			│		
	│	│			  │			│
	│	│			  │			│
	│	├──────┼──────┤
	│	│			  │			│
	│	│			  │			│
	│	│			  │			│
	│	└──────┴──────┘
	│bottom
	┴────────────────────→
	0										x
*/

//AreaManager 职责根据场景id来获得area

class ObjManager;
class AreaManager
{
public:
	AreaManager():
	m_max_aoi_handle(0)
	{
	}
	~AreaManager();

	void		Init(short unit_x,short unit_y,short max_x,short max_y);
	static void CreateAreaMatrix(AreaManager *am, short unit_x, short unit_y, short max_x, short max_y);
	void		ReleaseAreaMatrix();

	//当一个新对象（obj）进入场景的时候，该obj的视野将会成为aoi；同时该对象又成为了观察者
	UInt32		GreateObserver(ObjID obj_id);
    void		CreateAOI(ObjID obj_id, Posi center, Posi enter_radius, Posi leave_radius);

	void		MoveObserver(UInt32 observer_handle);
    void		MoveAOI(UInt32 aoi_handle);

	void		EraseObserver(UInt32 observer_handle);
	void		EraseAOI(UInt32 aoi_handle);


protected:
	void        GetArea(Posi &area, Coord x, Coord y);				
	bool		CheckArea(Posi &area, const Posi &p);				
private:
	
	short m_max_x;			// 整个场景的最大x长度
	short m_max_y;			// 整个场景的最大y长度

	short m_unit_x;			// 每个area的x长度
	short m_unit_y;			// 每个area的y长度

	short m_x_num;			// 横坐标有x个area
	short m_y_num;			// 纵坐标有y个area

	Area **						m_area_matrix;
	game::Array<AOI>			m_aoi_pool;
	game::Array<Observer *>		m_observer_pool;
    game::Vector<UInt32>		m_aoi_handle_pool;
    UInt32						m_max_aoi_handle;
	ObjManager *				m_obj_manager;
};

#endif
