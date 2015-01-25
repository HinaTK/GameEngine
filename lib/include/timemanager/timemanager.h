#ifndef GAMETIMEMANAGER_H
#define GAMETIMEMANAGER_H

#include <time.h>
#include <list>

/*
	其它的时间事件都应该继续TimeEvent；
	并将时间事件加入到TimeEventManager进行管理
*/
class TimeEvent
{
protected:
	
public:
	TimeEvent()
		: beginTime(0)
		, endTime(0)
	{

	}
	time_t beginTime;
	time_t endTime;

public:
	bool Invalid(){return beginTime == 0;}
	virtual void OnTime(){};
	virtual void OnEndTime(){};
};

class TimeEventManager
{
public:
	TimeEventManager();
	~TimeEventManager();
	void	AddEvent(TimeEvent *e);
	
	void	Update(time_t now);

private:
	void	AddEndEvent(TimeEvent *e);

	typedef std::list<TimeEvent *> TIME_EVENT_LIST;
protected:

	TIME_EVENT_LIST m_event_list;		// 记录所有未开始的时间事件
	TIME_EVENT_LIST m_event_end_list;	// 记录所有需要结束通知的时间事件
	TIME_EVENT_LIST::iterator m_itr;
	time_t	m_update_time;				// 下次更新的时间
};



#endif