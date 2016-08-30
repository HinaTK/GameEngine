
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
	// todo ȥ���ڴ濽��
	// todo дһ���µĽṹ�壬����handle
	m_manager->GetManager()->SendMsg(m_gate_id, 123, len, data);
}

