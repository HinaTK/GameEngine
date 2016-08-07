
#include "logmanager.h"
#include "log.h"


LogManager::LogManager(const char *dir_name)
{

}

void LogManager::AddLog(Log *log)
{
	m_log_vector.push_back(log);
}

void LogManager::Flush()
{
	for (std::vector<Log *>::iterator itr = m_log_vector.begin(); itr != m_log_vector.end(); ++itr)
	{
		(*itr)->Flush();
	}
}

