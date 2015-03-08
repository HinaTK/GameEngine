
#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <time.h>

class GameTime
{
public:
	GameTime();
    ~GameTime(){}
	time_t				Time();									// 获得当前时间戳
	unsigned long long	MilliSecond();							// 获得当前时间（毫秒）
    int					Day();									// 格式20130818
	int					Hour();									// 格式13
    int					Second();								// 格式144635  时分秒
	static	void		GameSleep(unsigned int ms);
	

	void				Update();

private:
	time_t				m_now;
	unsigned long long	m_now_ms;
	tm					*m_tm;
};

#endif // GAMETIME_H

