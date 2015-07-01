
#include "redis.h"
#include "redisprotocol.h"
#include "lib/include/frame/netmanager.h"
#include "lib/include/frame/msgcallback.h"

Redis::Redis()
: m_net_manager(NULL)
, m_net_handle(0)
{

}

Redis::~Redis()
{

}

bool Redis::Connect(char *ip, unsigned short port, Listener *lister)
{
	m_net_manager = lister->GetNetManager();
	m_net_handle = m_net_manager->ConnectServer(ip, port, lister);
	if (m_net_handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	return true;
}

void Redis::Command(const char *command, unsigned int length)
{
	m_net_manager->Send(m_net_handle, command, length);
}

RedisListener::RedisListener(NetManager *manager, MsgCallBack *call_back)
: Listener(manager)
{
	m_call_back_handle = manager->RegisterCallBack(call_back);
}

bool RedisListener::AnalyzeBuf()
{
	do
	{
		const char *buf = m_recv_buf.GetBuf();
		RedisBulkData *bulk_data = NULL;
		int read_len = RedisProtocol::Decode(buf, m_recv_buf.Length(), &bulk_data);
		if (read_len == RedisProtocol::OPR_DATA_INVALID)
		{
			// 数据出错，需要用log记录
			return false;
		}
		else if (read_len == RedisProtocol::OPR_MORE_DATA)
		{
			return true;
		}

		m_net_manager->PushMsg(this, buf, read_len);

		m_recv_buf.RemoveBuf(read_len);
	} while (true);

	return true;
}
