
#ifndef GATE_THREAD_H
#define GATE_THREAD_H

#include <queue>
#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamehash.h"
#include "common/datastructure/msgqueue.h"
#include "common/datastructure/gamearray.h"

class ThreadManager;
class GateThread : public SocketThread
{
public:
	virtual ~GateThread(){}
	GateThread(ThreadManager *manager, int index, ThreadID global);

	void	Dispatch(unsigned int msg_id, NetMsg &msg);
	unsigned int RegRole(NetHandle handle);
	void	DelRole(unsigned int index);
	void	PushCreator(NetHandle handle);

protected:
	bool	Init();
	void	Ready();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	struct CreatorInfo
	{
		NetHandle 	handle;
		time_t		timeout;
	};
	NetHandle		m_cneter_handle;
	int				m_index;
	/*
		新建立的role在这里注册一个消息队列，将索引设置给listener
	*/
	typedef game::Array<MsgQueue<NetMsg> *> ROLE_MSG;
	ROLE_MSG		m_role_msg;
	ThreadID		m_global;
	
	/*
		创建creator,并将其句柄放到这个队列，定时检查超时，并判断类型是否是Creator
		问题：这个句柄并不是唯一的（有可能Creator释放了，其它的Creator再申请到这个句柄）
		解决：在Creator中加入一个唯一的id（由时间和自增构成），当超时判断的时候，判断类型与这个id都是否相同，相同则删除
	*/
	std::queue<CreatorInfo> m_creator;
};

namespace New
{
	EXPORT GateThread * _GateThread(ThreadManager *manager, int index, ThreadID id);
}
#endif