
#include <stdlib.h>
#include "timer.h"
//#include "gametime.h"


TimerManager::TimerManager() 
: m_update_time(0)
{

}

// todo release the event pointer
TimerManager::~TimerManager()
{
}

void TimerManager::AddEvent(time_t interval, TimeEvent *e)
{
	m_event_heap.Push(Timer(time(NULL) + interval, e));
}

bool TimerManager::Update(time_t now)
{	
	bool ret = false;
	Timer timer;
	while (m_event_heap.Front(&timer))
	{
		if (timer.trigger_time <= now)
		{
			timer.event->OnTime();
			timer.event->Free();
			m_event_heap.PopFront();
		}
		else
		{
			break;
		}
		ret = true;
	}
	return ret;
}


void TimerQueue::AddEvent(TimeEvent *e)
{
	m_queue.push(Timer{ time(NULL) + m_interval, e });
}

EXPORT bool TimerQueue::Update(time_t now)
{
	if (m_queue.size() > 0 && now >= m_update_time)
	{
		do 
		{
			Timer &timer = m_queue.front();
			if (now >= timer.time_out)
			{
				timer.event->OnTime();
				timer.event->Free();
				m_queue.pop();
			}
			else
			{
				m_update_time = timer.time_out;
				break;
			}
		} while (m_queue.size() > 0);
		return true;
	}
	return false;
}

TimerQueue::TimerQueue(int interval)
: m_update_time(0)
, m_interval(interval)
{
	
}

TimerQueue::~TimerQueue()
{
	while (m_queue.size() > 0)
	{
		delete m_queue.front().event;
		m_queue.pop();
	}
}


TimerManager * New::_TimerManager()
{
	return new TimerManager();
}

TimerQueue * New::_TimerQueue(int interval)
{
	return new TimerQueue(interval);
}

void Delete::_TimerQueue(TimerQueue * queue)
{
	delete queue;
}

void Delete::_TimerManager(TimerManager *tm)
{
	delete tm;
}
