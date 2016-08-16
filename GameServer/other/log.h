#ifndef LOG_H
#define LOG_H

// #ifdef __LINUX__

// #include <time.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <string.h>
// #include <string>
// #include <stdarg.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <fcntl.h>
// using namespace std;

// class Log
// {
// public:
//     Log();

//     Log &Instance()
//     {
//         static Log log;
//         return log;
//     }

//     //保存日志的目录为../Log/filename/日期（每日）/时间（每30分钟）.log
//     //例如：../Log/rolelogin/20130630/201306301800.log
//     //将30分钟内的所有日志写进同一个.log中
//     void WriteLog(string filename, char *logformat, ...);

//     void LogForMat();


// private:
//     char * MakePath(string filename);

//     string GetWriteLogTime();

//     char m_log[1024];



//     struct tm *m_t;

//     //string m_log;
// };

// #endif // LOG_H

#endif