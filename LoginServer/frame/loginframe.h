#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include "frame/frame.h"
#include "common/commonvariable.h"
#include "common/datastructure/msgqueue.h"
#include "libcommon/thread.h"
#include "message/messagefunction/messagehandler.h"

class LoginFrame : public Frame
{
public:
	static const UInt32 UpdateSleepTime = 80;		// ��λ���룬ÿ��80�������һ��
	static const UInt32 SendSleepTime = 50;			// ��λ���룬��������Ϣ����Ϊ��ʱ��˯��50����
	static const UInt32 RecvSleepTime = 50;			// ��λ���룬��������Ϣ����Ϊ�պ�û�е�����ʱ�䣬˯��50����

    ~LoginFrame();

    static LoginFrame &Instance()
    {
        static LoginFrame frame;
        return frame;
    }

	bool	InitConfig();
    /*
     *Init ��Ҫ�Ǽ������ã�����dll���ص���ܵ���
     */
    bool Init();    //��ʼ��

    /*
     *Update ��Ҫ�Ǹ���һЩ״̬�����統�ͻ��˷��͹�����һЩ���ݣ����̼�ͨ�ŵ�һЩ���ݣ����趨һ����ʱ����������update
     */
    void Update();  //����

	void	Exit();
	void	Wait();
	void	Recv(GameMsg *msg);

	void OnRecv(NetID user_id, char *msg, UInt16 length);

	void OnSend(NetID user_id, char *msg, UInt16 length);

	MsgQueue	*GetSendQueue(){ return &m_send_queue; }

	MsgQueue	*GetRecvQueue(){ return &m_recv_queue; }

public:
	Thread	m_recv_client_thread;
	Thread	m_recv_server_thread;
	Thread	m_send_thread;
    NetID	m_database_server_net_id;
	NetID	m_gateway_server_net_id;

private:
	LoginFrame();

	//TimeEventManager m_time_event_manager;
	MessageHandler		m_message_handler;
	
	MsgQueue			m_send_queue;
	MsgQueue			m_recv_queue;
};

#endif