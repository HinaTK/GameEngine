
#include "logmanager.h"
#include "log.h"


LogManager::LogManager()
: m_game_time(NULL)
{

}

void LogManager::SetGameTime(GameTime *game_time)
{
	m_game_time = game_time;
}

void LogManager::AddLog(Log *log)
{
	m_log_vector.push_back(log);
}

void LogManager::Flush()
{
	for (std::vector<Log *>::iterator itr = m_log_vector.begin(); itr != m_log_vector.end(); ++itr)
	{
		(*itr)->Flush(m_game_time->Day(), m_game_time->Hour());
	}
}

