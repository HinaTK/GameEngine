
#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <vector>
#include "timemanager/gametime.h"

class Log;
class LogManager
{
public:
	LogManager();
	~LogManager(){};

// 	static LogManager &Instance()
// 	{
// 		static LogManager manager;
// 		return manager;
// 	}

	void	SetGameTime(GameTime *game_time);

	void	AddLog(Log *log);

	void	Flush();
private:
	
	std::vector<Log *>	m_log_vector;
	GameTime			*m_game_time;
};

#endif