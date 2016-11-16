
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include <vector>
#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/gamehash.h"

class ThreadManager;
class NetThread : public SocketThread
{
public:
	
	NetThread(ThreadManager *manager, int index);
	virtual ~NetThread(){}

	struct Route
	{
		NetHandle	handle;			// ���׽��������صľ��
		int			gate_net_id;	// ��ɫ�������ж�Ӧ�Ŀͻ�������id
	};

	// ����������������
	void	Recv(NetMsg *msg);
	void	InnerRecv(NetMsg *msg);
protected:
	bool	Init();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
	bool	CMD(TPT type, ThreadID sid, int len, const char *data);

	void 	OnInnerRecv(const char *data, int length);
	void 	OnInnerRecvDisconnect(const char *data, int length);
private:
	typedef game::Array<Route>							PROXY_TO_GATE;	// ͨ������id,�ҵ���Ӧ������id
	typedef std::vector<game::Hash<int, NetHandle>>		GATE_TO_PROXY;	// ͨ�������̾���ͱ��������û�����id,�ҵ����ķ����û����
	NetHandle	m_server_handle;
	int			m_index;

	PROXY_TO_GATE	m_proxy;
	GATE_TO_PROXY	m_gate;

};

#endif