
#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <time.h>
#include "export.h"

class GameTime
{
public:
	GameTime();
    ~GameTime(){}
	time_t				Start(){ m_now = time(NULL); return m_now; }
	void				SetFPS(int ms);
	time_t				Time();									// 获得当前时间戳
	
	unsigned long long	MilliSecond();							// 获得当前时间（毫秒）
	unsigned long long	FrameTime();
	tm *				LocalTime();
    int					Day();									// 格式20130818
	int					Hour();									// 格式13
    int					DaySecond();							// 格式144635  时分秒

	void				Update();
	
private:
	time_t				m_now;
	unsigned long long	m_frame_time_ms;
	tm					*m_tm;
	int					m_day_id;
	int					m_sceond_id;
	unsigned long long	m_FPS;		// 毫秒
};

namespace TimeUtil
{
	static const time_t A_DAY 	= 24 * 3600;
	static const time_t A_WEEK	= 7 * A_DAY;

	inline time_t 	Now(){return time(NULL);}

	EXPORT time_t	Today();
	EXPORT time_t	Today(time_t now);

	EXPORT int 		WeekDay();
	EXPORT int 		WeekDay(time_t now);

	EXPORT time_t	NextWeek(int day);
	EXPORT time_t	NextWeek(time_t now, int day);
};

#endif // GAMETIME_H

