
#include "loginscene.h"
#include "obj/role.h"

LoginScene::LoginScene(ThreadManager *thread_manager)
: BaseThread(thread_manager)
{
	m_name = "loginscene";
}

LoginScene::~LoginScene()
{

}

bool LoginScene::Init()
{
	return true;
}

bool LoginScene::Run()
{
	if (m_role_manager.Size() > 0)
	{
		for (game::Vector<Role *>::iterator itr = m_role_manager.Begin(); itr != m_role_manager.End(); ++itr)
		{
			(*itr)->Dispatch();
		}
		return true;
	}
	return false;
}

void LoginScene::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case TProto::S_GATE_REG_ROLE:
		TProto::sGateRegRole *grr = (TProto::sGateRegRole *)data;
		m_role_manager.Push(new Role((MsgQueue<NetMsg> *)grr->queue, grr->index, grr->gate_id, grr->handle));
		break;


	default:
	}
}
