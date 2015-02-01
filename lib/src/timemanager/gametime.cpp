
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
    return time(NULL);
}

int GameTime::Day()
{
    static tm     *t       = NULL;
    static time_t gametime = 0;
    static int    day      = 0;
    time(&gametime);
    t = localtime(&gametime);

    day =  t->tm_mday;
    day = (t->tm_mon  + 1)    * 100   + day;
    day = (t->tm_year + 1900) * 10000 + day;
    return day;
}

int GameTime::Hour()
{
	static tm     *t = NULL;
	static time_t gametime = 0;
	time(&gametime);
	t = localtime(&gametime);
	return t->tm_hour;
}

int GameTime::Second()
{
    static tm     *t       = NULL;
    static time_t gametime = 0;
    static int    second   = 0;
    time(&gametime);
    t = localtime(&gametime);

    second = t->tm_sec;
    second = t->tm_min  * 100   + second;
    second = t->tm_hour * 10000 + second;
    return second;
}


bool GameTime::TimeInterval(int s,int ms)
{
//     if ((s < 0 || ms < 0) || (s == 0 && ms == 0))       //
//     {
//        return true;
//     }
//     static bool firstin = true;
//     static int second = time(NULL);
//     static int millisecond = 0;
// #ifdef WIN32
// 	static SYSTEMTIME wtm;
// 	if (firstin)
// 	{
// 		GetLocalTime(&wtm);
// 		firstin = false;
// 		return false;
// 	}
// #endif
// #ifdef __unix
// 	static struct timeval tv;
// 	if (firstin)
// 	{
// 		gettimeofday(&tv,NULL);
// 
// 		GetLocalTime(&wtm);
// 		firstin = false;
// 		return false;
// 	}
// 	struct timeval tvtemp;
// 	gettimeofday(&tvtemp,NULL);
// #endif
// 
//     if(time(NULL) > second + s)
//     {
//         firstin = true;
//         return true;
//     }
//     else if(time(NULL) == second + s)
//     {
//         if (ms > 1000)
//         {
//             ms = 999;
//         }
//         if (tvtemp.tv_usec - tv.tv_usec >= ms * 1000)
//         {
//             firstin = true;
//             return true;
//         }
// 
//     }

    return false;
}


bool GameTime::TimeIntervalOne(int s,int ms)
{
//     if ((s < 0 || ms < 0) || (s == 0 && ms == 0))       //
//     {
//        return true;
//     }
//     static bool isfinish = false;
// 
//     if (isfinish)
//     {
//         return false;
//     }
// 
//     static bool firstin = true;
//     static struct timeval tv;
// 
//     if (firstin)
//     {
//         gettimeofday(&tv,NULL);
//         firstin = false;
//         return false;
//     }
//     static struct timeval tvtemp;
//     gettimeofday(&tvtemp,NULL);
//     if(tvtemp.tv_sec > tv.tv_sec + s)
//     {
//         firstin = true;
//         isfinish = true;
//         return true;
//     }
//     else if(tvtemp.tv_sec == tv.tv_sec + s)
//     {
// 
//         if (ms > 1000)
//         {
//             ms = 999;
//         }
//         if (tvtemp.tv_usec - tv.tv_usec >= ms * 1000)
//         {
//             firstin = true;
//             isfinish = true;
//             return true;
//         }
//         //return false;
//     }

    return false;
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

unsigned long long GameTime::MilliSecond()
{
#ifdef __unix
	static struct timeval tv;
	gettimeofday(&tv, NULL);
	return (unsigned long long)(tv.tv_sec * 1000 + tv.tv_usec * 0.001);
#endif
#ifdef WIN32
	return (unsigned long long)GetTickCount64();
// 	static SYSTEMTIME st;
// 	GetLocalTime(&st);
// 	return st.wSecond * 1000 + st.wMilliseconds;
#endif
}



