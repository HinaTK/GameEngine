
#ifndef MESSAGE_H
#define MESSAGE_H

#include "lib/include/base/netcommon.h"
#include "lib/include/common/memoryvl.h"
#include "common/serverdef.h"

class MsgMemoryManager
{
public:
	MsgMemoryManager();
	~MsgMemoryManager();

	void	Alloc(char **buf, const char* data, unsigned int length);
	char *	Alloc(unsigned int length);
	template<typename T> void Free(T &msg){if (msg.length > 0) memory->Free(msg.data);};
private:
	MemoryVL *memory;
};

// 网络消息
class NetMsg
{
public:
	NetMsg();
	NetMsg(NetHandle _handle, unsigned int _length);
	NetMsg(NetHandle _handle, char *_data, unsigned int _length);
	~NetMsg();

	NetHandle		handle;
	unsigned int	length;
	char *			data;
};

class NetGlobalMsg
{
public:
	NetGlobalMsg(ThreadID _id, NetHandle _handle, unsigned short _length, char *_data);
	~NetGlobalMsg();
	ThreadID		id;
	NetHandle		handle;
	unsigned short	length;
	char *			data;
};

// 线程消息
class ThreadClass;
class ThreadMsg
{
public:
	ThreadMsg();
	ThreadMsg(TPT _type, char *_data);
	ThreadMsg(ThreadID _id, TPT _type, char *_data);
	ThreadMsg(ThreadID _id, TPT _type, int _length, const char *_data, MsgMemoryManager *memory);
	~ThreadMsg();
	
	ThreadID	id;
	TPT			type;	// 消息类型
	int			length;
	char		*data;
};

class MsgCallBack
{
public:
	MsgCallBack(){}
	~MsgCallBack(){}

	virtual void Accept(NetHandle handle, const char *ip){};

	virtual void Recv(NetMsg *msg) = 0;

	virtual void Disconnect(NetHandle handle, int err, int reason) = 0;
};

class BaseMsg
{
public:
	BaseMsg(MsgCallBack *call_back) :m_call_back(call_back){}
	~BaseMsg(){}

	enum MsgType
	{
		MSG_ACCEPT = 0,
		MSG_RECV,
		MSG_DISCONNECT,
		MSG_MAX
	};

	virtual void Recv(NetMsg *msg){};
	MsgCallBack *m_call_back;
};

// class RecvMsg
// {
// public:
// 	RecvMsg(MsgCallBack *call_back) :m_call_back(call_back)
// 	{
// 		// todo 测试函数绑定与用数组查询，那个快
// 		Exe[MSG_ACCEPT] 	= &RecvMsg::Accept;
// 		Exe[MSG_RECV] 		= &RecvMsg::Recv;
// 		Exe[MSG_DISCONNECT] = &RecvMsg::Disconnect;
// 	}
// 	~RecvMsg(){delete m_call_back;}

// 	enum MsgType
// 	{
// 		MSG_ACCEPT = 0,
// 		MSG_RECV,
// 		MSG_DISCONNECT,
// 		MSG_MAX
// 	};
// 	typedef void (RecvMsg::*Func[MSG_MAX])(NetMsg *msg);

// 	Func	Exe;

// 	inline void	TT(int t, NetMsg *msg){(this->*Exe[t])(msg);}

// 	void	Accept(NetMsg *msg){m_call_back->Accept(msg->handle, msg->data);}
// 	void 	Recv(NetMsg *msg){ m_call_back->Recv(msg); }
// 	void	Disconnect(NetMsg *msg)
// 	{
// 		NetCommon::ErrInfo *info = (NetCommon::ErrInfo *)msg->data;
// 		m_call_back->Disconnect(msg->handle, info->err, info->reason);
// 	}
	
// private:
// 	MsgCallBack *m_call_back;
// };

class AcceptMsg : public BaseMsg
{
public:
	AcceptMsg(MsgCallBack *call_back) :BaseMsg(call_back){}
	virtual void Recv(NetMsg *msg){ m_call_back->Accept(msg->handle, msg->data); };
};

class RecvMsg : public BaseMsg
{
public:
	RecvMsg(MsgCallBack *call_back) :BaseMsg(call_back){}
	virtual void Recv(NetMsg *msg){ m_call_back->Recv(msg); }
};

class DisconnectMsg : public BaseMsg
{
public:
	DisconnectMsg(MsgCallBack *call_back) :BaseMsg(call_back){}
	virtual void Recv(NetMsg *msg)
	{ 
		NetCommon::ErrInfo *info = (NetCommon::ErrInfo *)msg->data;
		m_call_back->Disconnect(msg->handle, info->err, info->reason);
	}
};

class MsgHandler
{
public:
	MsgHandler(MsgCallBack *call_back);
	~MsgHandler();

	inline void Recv(NetMsgType msg_type, NetMsg &msg)
	{
		m_bm[msg_type]->Recv(&msg);
	}
private:
	BaseMsg *m_bm[BaseMsg::MSG_MAX];
};

#endif