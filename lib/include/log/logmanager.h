
#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <vector>

class Log;
class LogManager
{
public:
	~LogManager(){};

	static LogManager &Instance()
	{
		static LogManager manager;
		return manager;
	}

	void	AddLog(Log *log);

	void	Flush();
private:
	LogManager(){};

	std::vector<Log *> m_log_vector;
};

#endif