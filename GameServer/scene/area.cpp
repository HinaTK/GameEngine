
#include "area.h"

Area::~Area(void)
{
}

void Area::Init( short bottom_x,short bottom_y,short top_x,short top_y )
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














