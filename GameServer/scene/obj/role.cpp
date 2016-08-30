
#include "role.h"
#include "scene/scenemanager.h"


Role::Role(SceneManager *manager, ThreadID gate_id, NetHandle handle)
: m_manager(manager)
, m_gate_id(gate_id)
, m_handle(handle)
{

}

Role::~Role()
{

}

void Role::Send(int len, char *data)
{
	// todo 去掉内存拷贝
	// todo 写一个新的结构体，加上handle
	m_manager->GetManager()->SendMsg(m_gate_id, 123, len, data);
}

