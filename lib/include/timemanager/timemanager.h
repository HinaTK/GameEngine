
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <time.h>
#include "gametime.h"
#include "common/datastructure/gameheap.h"

/*
	其它的时间事件都应该继承TimeEvent；
	并将时间事件加入到TimeEventManager进行管理
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

	GameTime			*GetGameTime(){ return &m_game_time; }
// 	time_t				Time(){ return m_game_time.Time(); }
// 	unsigned long long	MilliSecond(){ return m_game_time.MilliSecond(); }
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
	GameTime		m_game_time;
	time_t	m_update_time;				// 下次更新的时间
};



#endif