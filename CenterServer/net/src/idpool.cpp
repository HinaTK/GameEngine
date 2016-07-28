
#include "idpool.h"
#include "threadproto.h"
#include "net/netthread.h"


IDPool::IDPool(NetThread *t)
: m_thread(t)
, m_index(0)
{

}

unsigned int IDPool::GetID()
{
	if (m_index >= ID_POOL_MAX_INDEX)
	{
		for (unsigned int i = 0; i < ID_POOL_MAX_INDEX; ++i)
		{
			// todo ע����m_max_id
			m_pool[i] = m_max_id++;
		}
		m_index = 0;
		m_thread->GetManager()->SendMsg(ThreadProto::TP_SAVE_ROLE_MAX_ID, m_thread->GetThreadID(), sizeof(unsigned int), (const char *)&m_max_id, m_thread->GetID());
	}
	return m_pool[m_index++];
}


