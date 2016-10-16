
#include "global.h"
#include "temprole.h"
#include "proto.h"
#include "lib/include/gate/proto.h"

Global::Global(ThreadManager *thread_manager)
: BaseThread(thread_manager)
{
	m_name = "global";
}

Global::~Global()
{

}

bool Global::Init()
{
	return true;
}

bool Global::Run()
{
	if (m_role_manager.Size() > 0)
	{
		for (game::Vector<TempRole *>::iterator itr = m_role_manager.Begin(); itr != m_role_manager.End(); ++itr)
		{
			(*itr)->Dispatch();
		}
		return true;
	}
	return false;
}

void Global::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case TProto::S_GATE_REG_ROLE:
		TProto::sGateRegRole *grr = (TProto::sGateRegRole *)data;
		m_role_manager.Push(TempRole((MsgQueue<NetMsg> *)grr->queue, grr->index, grr->gate_id, grr->handle));
		break;
	case TProto::TO_GLOBAL_LOAD_ROLE:
		// todo 将各数据模块初始化到角色并进入场�?
	case TProto::R_GLOBAL_LOGOUT:
		RoleLogout((Role *)data);
		break;
	default:
		break;
	}
}

void Global::RoleLogin(RoleID rid)
{

}

void Global::RoleLogout(Role *role)
{
	m_role_cache.Push(role);
}