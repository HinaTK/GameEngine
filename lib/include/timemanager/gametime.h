
#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <time.h>

class GameTime
{
public:
	GameTime();
    ~GameTime(){}
    static	time_t				Time();							// 获得当前时间戳
    static	int					Day();							// 格式20130818
	static	int					Hour();							// 格式13
    static	int					Second();						// 格式144635  时分秒
    static	bool				TimeInterval(int s,int ms);		// 时间间隔单位为秒
    static	bool				TimeIntervalOne(int s,int ms);	// 时间间隔单位为秒 只执行一次
	static	void				GameSleep(unsigned int ms);
	static	unsigned long long	MilliSecond();					// 获得当前时间（毫秒）


};

#endif // GAMETIME_H

