#ifndef _AREAMANAGER_H
#define _AREAMANAGER_H

#include "GuiMi/define.h"
#include "aoi.h"
#include "area.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"

#include "observer.h"


/*
   y��
	��
	��	���������������Щ�������������top
	��	��			  ��			��		
	��	��			  ��			��
	��	��			  ��			��
	��	���������������੤������������
	��	��			  ��			��
	��	��			  ��			��
	��	��			  ��			��
	��	���������������ة�������������
	��bottom
	�ة�����������������������������������������
	0										x
*/

//AreaManager ְ����ݳ���id�����area

class ObjManager;
class AreaManager
{
public:
	AreaManager(ObjManager *obj_manager)
		: m_max_aoi_handle(0)
		, m_obj_manager(obj_manager)
	{
	}
	~AreaManager();

	void		Init(short unit_x, short unit_y, short max_x, short max_y);
	static void CreateAreaMatrix(AreaManager *am, short unit_x, short unit_y, short max_x, short max_y);
	void		ReleaseAreaMatrix();

	//��һ���¶���obj�����볡����ʱ�򣬸�obj����Ұ�����Ϊaoi��ͬʱ�ö����ֳ�Ϊ�˹۲���
	UInt32		GreateObserver(ObjID obj_id);
	void		CreateCircleAOI(ObjID obj_id, const Posi &centre, int radius);
	void		CreateRectAOI(ObjID obj_id, const Posi &center, int aoi_x, int aoi_y);

	void		MoveObserver(UInt32 observer_handle);
    void		MoveAOI(UInt32 aoi_handle);

	void		EraseObserver(UInt32 observer_handle);
	void		EraseAOI(UInt32 aoi_handle);


protected:
	void		CreateAOI(ObjID obj_id, const Posi &center, Posi &radius, bool is_circle = false);
	void        GetArea(Posi &area, Coord x, Coord y);				
	bool		CheckArea(Posi &area, const Posi &p);				
private:
	
	short m_max_x;			// �������������x����
	short m_max_y;			// �������������y����

	short m_unit_x;			// ÿ��area��x����
	short m_unit_y;			// ÿ��area��y����

	short m_x_num;			// ��������x��area
	short m_y_num;			// ��������y��area

	Area **						m_area_matrix;
	game::Array<AOI>			m_aoi_pool;
	game::Array<Observer *>		m_observer_pool;
    game::Vector<UInt32>		m_aoi_handle_pool;
    UInt32						m_max_aoi_handle;
	ObjManager *				m_obj_manager;
};

#endif