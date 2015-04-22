
#include "area.h"

Area::~Area(void)
{
}

void Area::Init(Coord bottom_x, Coord bottom_y, Coord top_x, Coord top_y)
{
	m_bottom_x	= bottom_x;
	m_bottom_y	= bottom_y;
	m_top_x		= top_x;
	m_top_y		= top_y;
}

UInt32 Area::AddObserver( ObjID obj_id )
{
	return m_observer_list.Push(obj_id);
}

void Area::EraseObserver( ObjID obj_id )
{
	m_observer_list.Erase(obj_id);
}

int Area::GetAOIHandle( UInt32 index )
{
	if (index >= m_aoi_handle_list.Size())
	{
		return Area::INVALID_AOI_HANDLE;
	}
	return m_aoi_handle_list[index];
}

// 获取该区域的AOI个数，也就是对该区域感兴趣的对象个数
UInt32 Area::GetAOISize()
{
	return m_aoi_handle_list.Size();
}

void Area::EraseAOIHandle( int aoi_handle )
{
	m_aoi_handle_list.Erase(aoi_handle);
}

void Area::AddAOIHandle( int aoi_handle )
{
	m_aoi_handle_list.Push(aoi_handle);
}














