
#include <stdlib.h>
#include "timer.h"
//#include "gametime.h"


TimerManager::TimerManager() 
: m_update_time(0)
{

}

TimerManager::~TimerManager()
{
}

void TimerManager::AddEvent(time_t interval, TimeEvent *e)
{
	m_event_heap.Push(Timer(time(NULL) + interval, e));
}

bool TimerManager::Update(time_t now)
{	
	if (now >= m_update_time)
	{
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
				m_update_time = timer.trigger_time;
				break;
			}
		}
		return true;
	}
	return false;
}


TimerManager * New::_TimerManager()
{
	return new TimerManager();
}
