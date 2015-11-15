#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include "frame/frame.h"
#include "common/commonvariable.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/thread.h"
#include "lib/include/rpc/rpcserver.h"
#include "message/messagefunction/messagehandler.h"

class OuterCallBack;
class InnerCallBack;
class NewFrame : public Frame
{
public:
	static const UInt32 UpdateSleepTime = 80;		// 单位毫秒，每隔80毫秒更新一次
	static const UInt32 SendSleepTime = 50;			// 单位毫秒，当发送消息队列为空时，睡眠50毫秒
	static const UInt32 RecvSleepTime = 50;			// 单位毫秒，当接收消息队列为空和没有到更新时间，睡眠50毫秒

    ~NewFrame();

    static NewFrame &Instance()
    {
        static NewFrame frame;
        return frame;
    }

	bool		InitConfig();
   
    bool		Init();    //初始化

	void		Update(unsigned int interval, time_t now);

	void		Exit();
	void		Wait();
	void		Recv(GameMsg *msg);

public:
	void		OnLoginReq(NetHandle handle, char *data, unsigned int length);
public:
	NetHandle	m_login_server_handle;
    NetHandle	m_database_server_handle;
	SOCKET		m_gateway_server_net_id;

private:
	NewFrame();

	//TimeEventManager m_time_event_manager;
	MessageHandler		m_message_handler;
	//RPCServer			m_rpc_server;
	OuterCallBack		*m_o_call_back;
	InnerCallBack		*m_i_call_back;
};

#endif