
#include "role.h"
#include "scene/scenemanager.h"


Role::Role(MsgQueue<NetMsg> *queue, unsigned int index, ThreadID gate_id, NetHandle handle)
: m_msg_queue(queue)
, m_msg_index(index)
, m_gate_id(gate_id)
, m_handle(handle)
{

}

Role::~Role()
{

}

bool Role::Init(SceneManager *manager)
{
	return true;
}

void Role::Send(int len, char *data)
{
	// todo ȥ���ڴ濽��
	// todo дһ���µĽṹ�壬����handle
	m_manager->GetManager()->SendMsg(m_gate_id, 123, len, data);
}

void Role::Logout()
{
	m_manager->GetManager()->SendMsg(m_gate_id, )
}


