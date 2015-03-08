
#include <stdlib.h>
#include "timemanager.h"



TimeEventManager::TimeEventManager() 
: m_update_time(0)
{

}

TimeEventManager::~TimeEventManager()
{
}

void TimeEventManager::AddEvent(time_t interval, TimeEvent *e)
{
	m_event_heap.Push(Timer(time(NULL) + interval, e));
}

void TimeEventManager::Update()
{	
	m_game_time.Update();
	time_t now = m_game_time.Time();
	if (now >= m_update_time)
	{
		Timer timer;
		while (m_event_heap.Front(&timer))
		{
			if (timer.trigger_time <= now)
			{
				timer.event->OnTime();
				timer.event->Free();
				break;
			}
			else
			{
				m_update_time = timer.trigger_time;
				break;
			}
		}
	}
}

