
#include "frame/frame.h"
#include "libtimemanager.h"
#include "frame/netcommon.h"
#include "log/log.h"
#include "frame/message.h"

Frame::Frame()
: m_update_interval(200)
, m_ex_send_sleep_time(30)
, m_in_send_sleep_time(30)
{
	//m_in_com.SetFrame(this);
}

void *Listen(void * arg)
{
	Frame *frame = (Frame *)arg;
	if (frame == NULL)
	{
		return NULL;
	}
	//frame->GetInCom()->Listen();
	frame->GetNetManager()->Listen();
	return NULL;
}


void *WriteLog(void * arg)
{
	static const unsigned int sleepTime = 60 * 1000;
	while (true)
	{
		//Log::Instance().Flush();
		GameTime::GameSleep(sleepTime);
	}
	return NULL;
}

void Frame::Listen()
{
	m_listen_thread.Create(::Listen, this);
}

bool Frame::Run()
{
	GameMsg		**msg = NULL;
	MsgQueue	*recvQueue = m_net_manager.GetMsgQueue();
	int		lastTime = GameTime::GetMilliSecond();	// 上一次更新时间
	int		curTime = 0;
	int		second = 0;
	int		oneMinute = 60000;

	m_log_thread.Create(WriteLog);
	this->Listen();
	while (1)
	{
		curTime = GameTime::GetMilliSecond();
		if (!recvQueue->IsEmpty())
		{
			msg = recvQueue->Val();
			if ((*msg) != NULL)
			{
				if ((*msg)->net_id > 0)
				{
					this->InteanalRecv((*msg)->net_id, (*msg)->data.mem, (*msg)->length);
				}
				delete (*msg);
			}
		}
		else
		{
			second = curTime < lastTime ? oneMinute : 0;
			int interval = (curTime + second) - lastTime;
			if (interval < m_update_interval)
			{
				GameTime::GameSleep(m_in_send_sleep_time < m_update_interval - interval ? m_in_send_sleep_time : m_update_interval - interval);
			}
			curTime = (lastTime + m_update_interval) % oneMinute;
		}

		second = curTime < lastTime ? oneMinute : 0;
		if ((curTime + second) - lastTime >= m_update_interval)
		{
			//timeNow = GameTime::Instance().Time();
			Update(GameTime::Time());
			lastTime = curTime;
		}
	}
	return true;
}


// void Frame::Send(NetID net_id, char *msg, UInt32 length)
// {
// 	MsgQueue::ProtocolInfo info;
// 	info.net_id = net_id;
// 	memcpy(info.msg, msg, length);
// 	info.length = length;
// 	if (!m_in_com.SendQueue().Push(info))
// 	{
// 		Send(net_id, msg, length);
// 	}
// }



