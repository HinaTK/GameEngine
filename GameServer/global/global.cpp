
#include "global.h"
#include "scene/obj/role.h"
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
	return false;
}

void Global::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case TProto::S_GATE_REG_ROLE:
		TProto::sGateRegRole *grr = (TProto::sGateRegRole *)data;
		m_role_manager.Push(new Role((MsgQueue<NetMsg> *)grr->queue, grr->index, grr->gate_id, grr->handle));
		break;
// 	case LoginSceneTID::LOAD_ROLE:
// 		// todo ∑¢ÀÕµΩdb«Î«Û
// 		break;

	default:
	}
}
