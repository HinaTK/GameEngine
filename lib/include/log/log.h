
#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <string>
#include "common/datastructure/circlequeue.h"

/*
	存储格式：
	20150505->a.log
	20150506->a.log
*/
class Log
{
public:
	~Log();
	Log(const char *server_name, const char *log_name);

	void	Normal(char *log, ...);

	void	Warn(char *log, ...);

	void	Error(char *log, ...);

	void	Flush();				// 冲洗队列

	void *		operator new(size_t c);
	void		operator delete(void *m);

private:
	bool	MakeDayDir(int day);
	bool	MakeFile();

	FILE		*m_log_fp;
	std::string	m_root_dir;
	std::string	m_day_dir;
	std::string m_log_name;
	CircleQueue<std::string > m_queue;
	int			m_day;

};

#endif