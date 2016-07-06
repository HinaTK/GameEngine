
#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <time.h>

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
	static	void		Sleep(unsigned int ms);

	void				Update();

private:
	time_t				m_now;
	unsigned long long	m_frame_time_ms;
	tm					*m_tm;
	int					m_day_id;
	int					m_sceond_id;
	unsigned long long	m_FPS;		// 毫秒
};

#endif // GAMETIME_H

