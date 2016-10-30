
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
		for (game::Vector<TempRole>::iterator itr = m_role_manager.Begin(); itr != m_role_manager.End(); ++itr)
		{
			itr->Dispatch(this);
		}
		return true;
	}
	return false;
}

void Global::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	CASE(TProto::GLOBAL_REG_ROLE)
		TProto::sGateRegRole *grr = (TProto::sGateRegRole *)data;
		m_role_manager.Push(TempRole((MsgQueue<NetMsg> *)grr->queue, grr->index, grr->gate_id, grr->handle));
		BREAK();
	case TProto::GLOBAL_LOAD_ROLE:
		// todo 加载角色缓存信息，找不到则到数据找
	case TProto::GLOBAL_ROLE_LOGOUT:
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