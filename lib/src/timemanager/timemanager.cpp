#include <stdlib.h>
#include "timemanager.h"


TimeEventManager::TimeEventManager()
: m_update_time(0)
{
}

TimeEventManager::~TimeEventManager()
{
	TimeEvent *e = NULL;
	for (m_itr = m_event_list.begin(); m_itr != m_event_list.end();)
	{
		e = (*m_itr);
		m_itr = m_event_list.erase(m_itr);
		delete e;
	}
}

void TimeEventManager::AddEvent( TimeEvent *e )
{
	for (m_itr = m_event_list.begin(); m_itr != m_event_list.end(); m_itr++)
	{
		if (e->beginTime < (*m_itr)->beginTime)
		{
			m_event_list.insert(m_itr,e);
			break;
		}
	}
	m_itr = m_event_list.begin();
	if (m_itr != m_event_list.end())
	{
		if ((*m_itr)->beginTime < m_update_time)
		{
			m_update_time = (*m_itr)->beginTime;
		}
	}
}

void TimeEventManager::AddEndEvent(TimeEvent *e)
{
	for (m_itr = m_event_end_list.begin(); m_itr != m_event_end_list.end(); m_itr++)
	{
		if (e->endTime < (*m_itr)->endTime)
		{
			m_event_list.insert(m_itr, e);
			break;
		}
	}
}

void TimeEventManager::Update(time_t now)
{	
	if (now < m_update_time)
	{
		return;
	}
	for (m_itr = m_event_list.begin(); m_itr != m_event_list.end();)
	{
		if (now >= (*m_itr)->beginTime)
		{
			(*m_itr)->OnTime();
			if ((*m_itr)->endTime > (*m_itr)->beginTime)
			{
				AddEndEvent((*m_itr));
			}
			m_itr = m_event_list.erase(m_itr);
		}
		else
		{
			m_update_time = (*m_itr)->beginTime;
			break;
		}
	}

	for (m_itr = m_event_end_list.begin(); m_itr != m_event_end_list.end();)
	{
		if (now >= (*m_itr)->endTime)
		{
			(*m_itr)->OnEndTime();
			m_itr = m_event_end_list.erase(m_itr);
		}
		else
		{
			if ((*m_itr)->endTime < m_update_time)
			{
				m_update_time = (*m_itr)->endTime;
			}
			break;
		}
	}
}

