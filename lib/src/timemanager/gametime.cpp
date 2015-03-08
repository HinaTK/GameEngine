
#include "gametime.h"

#ifdef __unix
#include <sys/time.h>
#include <unistd.h>
#endif

#ifdef WIN32
#include <windows.h>
#endif

GameTime::GameTime()
{
}

time_t GameTime::Time()
{
	return m_now;
}

unsigned long long GameTime::MilliSecond()
{
	return m_now_ms;
}

int GameTime::Day()
{
	int day = m_tm->tm_mday;
	day = (m_tm->tm_mon + 1) * 100 + day;
	day = (m_tm->tm_year + 1900) * 10000 + day;
    return day;
}

int GameTime::Hour()
{
	return m_tm->tm_hour;
}

int GameTime::Second()
{
	int second = m_tm->tm_sec;
	second = m_tm->tm_min * 100 + second;
	second = m_tm->tm_hour * 10000 + second;
	return second;
}

void GameTime::GameSleep( unsigned int ms )
{
#ifdef __unix
	//usleep(ms * 1000);
	usleep((ms << 10) - (ms << 4) - (ms << 3));		// 经测试，这种方法在linux下执行得更快一些（windows下差不多）
#endif
#ifdef WIN32
	Sleep(ms);
#endif
}

void GameTime::Update()
{
	m_now = time(NULL);
	m_tm = localtime(&m_now);
#ifdef __unix
	static struct timeval tv;
	gettimeofday(&tv, NULL);
	m_now_ms = (unsigned long long)(tv.tv_sec * 1000 + tv.tv_usec * 0.001);
#endif
#ifdef WIN32
	m_now_ms = (unsigned long long)GetTickCount64();
#endif
}




