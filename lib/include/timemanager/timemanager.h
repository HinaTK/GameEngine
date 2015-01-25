#ifndef GAMETIMEMANAGER_H
#define GAMETIMEMANAGER_H

#include <time.h>
#include <list>

/*
	������ʱ���¼���Ӧ�ü���TimeEvent��
	����ʱ���¼����뵽TimeEventManager���й���
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

	TIME_EVENT_LIST m_event_list;		// ��¼����δ��ʼ��ʱ���¼�
	TIME_EVENT_LIST m_event_end_list;	// ��¼������Ҫ����֪ͨ��ʱ���¼�
	TIME_EVENT_LIST::iterator m_itr;
	time_t	m_update_time;				// �´θ��µ�ʱ��
};



#endif