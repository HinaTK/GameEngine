#ifndef _AREA_H
#define _AREA_H

#include "global/globalvariable.h"
#include "common/commonvariable.h"
#include "common/datastructure/gamevector.h"

/*
   y��
	��
	��	����������������top
	��	��			  ��
	��	��			  ��
	��	��			  ��
	��	����������������
	��bottom
	�ة���������������������
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
	void	Init(short bottom_x,short bottom_y,short top_x,short top_y);

	UInt32	AddObserver(ObjID obj_id);
	void	EraseObserver(ObjID obj_id);

	int		GetAOIHandle(UInt32 index);
	UInt32	GetAOISize();
	void	AddAOIHandle(int aoi_handle);
	void	EraseAOIHandle(int aoi_handle);

	OBSERVER_LIST *GetObserverList(){return &m_observer_list;}
private:
	
	short m_bottom_x;
	short m_bottom_y;
	
	short m_top_x;
	short m_top_y;

	OBSERVER_LIST			m_observer_list;		// �Ը�����Ĺ۲��б�	
	game::Vector<int>	m_aoi_handle_list;		// ���ж��������ĸо�Ȥ�ľ��

};

#endif
