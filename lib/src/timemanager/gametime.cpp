
#include "gametime.h"

#ifdef __unix
#include <sys/time.h>
#include <unistd.h>
#endif

#ifdef WIN32
#include <windows.h>
#endif

GameTime::GameTime()
: m_now(0)
, m_frame_time_ms(0)
, m_tm(NULL)
, m_day_id(0)
, m_sceond_id(0)
, m_FPS(250)
{
	Update();
}

void GameTime::SetFPS(int ms)
{
	m_FPS = ms;
}

time_t GameTime::Time()
{
	return m_now;
}

unsigned long long GameTime::MilliSecond()
{
#ifdef __unix
	static struct timeval tv;
	gettimeofday(&tv, NULL);
	return (unsigned long long)(tv.tv_sec * 1000 + tv.tv_usec * 0.001);
#endif
#ifdef WIN32
	return (unsigned long long)GetTickCount64();
#endif
}

unsigned long long GameTime::FrameTime()
{
	return m_frame_time_ms;
}

tm * GameTime::LocalTime()
{
	return m_tm;
}

int GameTime::Day()
{
    return m_day_id;
}

int GameTime::Hour()
{
	return m_tm->tm_hour;
}

int GameTime::DaySecond()
{
	return m_sceond_id;
}

void GameTime::Sleep( unsigned int ms )
{
#ifdef __unix
	usleep((ms << 10) - (ms << 4) - (ms << 3));		// 经测试，这种方法在linux下执行得更快一些（windows下差不多）
	//Sleep(ms);
#endif
#ifdef WIN32
	Sleep(ms);
#endif
}

void GameTime::Update()
{
	unsigned long long	now_ms = MilliSecond();
	if (now_ms - m_frame_time_ms >= m_FPS)
	{
		m_now = time(NULL);
		m_tm = localtime(&m_now);

		m_day_id = m_tm->tm_mday;
		m_day_id = (m_tm->tm_mon + 1) * 100 + m_day_id;
		m_day_id = (m_tm->tm_year + 1900) * 10000 + m_day_id;

		m_sceond_id = m_tm->tm_sec;
		m_sceond_id = m_tm->tm_min * 100 + m_sceond_id;
		m_sceond_id = m_tm->tm_hour * 10000 + m_sceond_id;

		m_frame_time_ms = now_ms;
	}
}




