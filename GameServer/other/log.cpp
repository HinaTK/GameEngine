#include "log.h"

#ifdef __LINUX__
// #define LOGFORMAT(FIELD)\
//     if(m_log == "")\
//     {\
//          m_log = #FIELD;\
//     }\
//     else\
//     {\
//         m_log = m_log + #FIELD;\
//     }\
//     m_log = m_log + "=";\
//     m_log = m_log + FIELD;\


// #define TIMEFORMAT(FORMAT,VAL)\
//     if(VAL < 10)\
//     {\
//         FORMAT = FORMAT + "0%d";\
//     }\
//     else\
//     {\
//         FORMAT = FORMAT + "%d";\
//     }\

// Log::Log()
// {
//     m_t = NULL;
// }

// //可以在logformat中加入 \n(\r,\n\r) 达到了换行的目的
// void Log::WriteLog(string filename,char *logformat,...)
// {
//     char *logname = MakePath(filename);
//     int fd = open(logname,O_RDWR|O_CREAT|O_APPEND,0777);
//     if (fd == -1)
//     {
//         fprintf(stderr, "%s \n", strerror(errno));
//         printf("%s Write log failed!\n",logname);
//         return ;
//     }

//     va_list args;
//     va_start(args,logformat);
//     vsprintf(m_log,logformat,args);
//     va_end(args);

//     string log = GetWriteLogTime() + m_log;
//     write(fd,log.c_str(),strlen(log.c_str()));
//     //m_log = "";

// }


// char * Log::MakePath(string filename)
// {
//     char *curpath = (char *)malloc(512);

//     getcwd(curpath,512);
//     string temp = "/Log/" + filename;
//     temp = curpath +temp;
//     string format = "%d";
//     char temptime[32];
//     time_t logtime;
//     time(&logtime);
//     m_t=localtime(&logtime);
//     if (m_t == NULL)
//     {
//         return NULL;
//     }
//     TIMEFORMAT(format,1 + m_t->tm_mon);
//     TIMEFORMAT(format,m_t->tm_mday);


//     sprintf(temptime,format.c_str(),1900 + m_t->tm_year,1 + m_t->tm_mon,m_t->tm_mday);
//     temp = temp + '/' + temptime;

//     int tempmin = 0;
//     if (0 < m_t->tm_min && m_t->tm_min < 30)
//     {
//         tempmin = 0;
//     }
//     else
//     {
//         tempmin = 30;
//     }

//     format = "";
//     TIMEFORMAT(format,m_t->tm_hour);
//     TIMEFORMAT(format,m_t->tm_min);

//     mkdir(temp.c_str(),0777);
//     sprintf(temptime,format.c_str(),m_t->tm_hour,tempmin);
//     temp = temp + '/' + temptime + ".log";

//     return (char *)temp.c_str();
// }

// string Log::GetWriteLogTime()
// {
//     char temptime[64];
//     string format = "%d";                   //
//     TIMEFORMAT(format,1 + m_t->tm_mon);     //
//     TIMEFORMAT(format,m_t->tm_mday);        //
//     TIMEFORMAT(format,m_t->tm_hour);
//     TIMEFORMAT(format,m_t->tm_min);
//     TIMEFORMAT(format,m_t->tm_sec);
//     sprintf(temptime,format.c_str(),1900 + m_t->tm_year,1 + m_t->tm_mon,m_t->tm_mday,m_t->tm_hour,m_t->tm_min,m_t->tm_sec);

//     string temp = "logtime=";
//     temp = temp + string(temptime) + ",";
//     return temp;
//     //return string(temptime);

// }

#endif