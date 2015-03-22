
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <time.h>
#include "common/datastructure/gameheap.h"

/*
	������ʱ���¼���Ӧ�ü̳�TimeEvent��
	����ʱ���¼����뵽TimeEventManager���й���
*/
class TimeEvent
{
public:
	TimeEvent(){};
	virtual void OnTime() = 0;
	virtual void Free() = 0;
};

class TimeEventManager
{
public:
	TimeEventManager();
	~TimeEventManager();

	void				AddEvent(time_t interval, TimeEvent *e);
	void				Update();
protected:
	struct Timer
	{
		Timer() :trigger_time(0), event(0) {}
		Timer(time_t _trigger_time, TimeEvent *_event) :trigger_time(_trigger_time), event(_event){}
		time_t trigger_time;
		TimeEvent *event;

		bool operator <(const Timer &v) const
		{
			return trigger_time < v.trigger_time;
		}

		bool operator >= (const Timer &v) const
		{
			return trigger_time >= v.trigger_time;
		}
	};

	typedef game::Heap<Timer>		TIME_EVENT_HEAP;
protected:
	TIME_EVENT_HEAP	m_event_heap;
	time_t	m_update_time;				// �´θ��µ�ʱ��
};



#endif