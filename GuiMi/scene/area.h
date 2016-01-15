#ifndef _AREA_H
#define _AREA_H

#include "define.h"
#include "common/commonvariable.h"
#include "common/datastructure/gamevector.h"

/*
   y↑
	│
	│	┌──────┐top
	│	│			  │
	│	│			  │
	│	│			  │
	│	└──────┘
	│bottom
	┴──────────→
	0					  x
*/
class Area
{
public:
	Area():
	m_observer_list(64),
	m_aoi_handle_list(64)
	{
	}
	~Area();
	static const int INVALID_AOI_HANDLE = -1;
	typedef game::Vector<ObjID> OBSERVER_LIST;
	void	Init(Coord bottom_x, Coord bottom_y, Coord top_x, Coord top_y);

	UInt32	AddObserver(ObjID obj_id);
	void	EraseObserver(ObjID obj_id);

	int		GetAOIHandle(UInt32 index);
	UInt32	GetAOISize();
	void	AddAOIHandle(int aoi_handle);
	void	EraseAOIHandle(int aoi_handle);

	OBSERVER_LIST *GetObserverList(){return &m_observer_list;}
private:
	
	Coord m_bottom_x;
	Coord m_bottom_y;
	
	Coord m_top_x;
	Coord m_top_y;

	OBSERVER_LIST		m_observer_list;		// 对该区域的观察列表	
	game::Vector<int>	m_aoi_handle_list;		// 所有对这个区域的感觉趣的句柄

};

#endif
