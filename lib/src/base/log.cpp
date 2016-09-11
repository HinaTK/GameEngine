
#ifdef __unix
#include <sys/stat.h>
#include <sys/types.h>
#endif // __unix

#include "log.h"
#include "function.h"
#include "lib/include/common/serverconfig.h"


// 同一个线程内，共用LogItem线程安全
// todo 不包含serverconfig，直接传参数进来，减少依赖

class LogTimeEvent : public TimeEvent
{
public:
	LogTimeEvent(TimerManager *timer_manager, Log *log, unsigned short index)
	: TimeEvent()
	, m_timer_manager(timer_manager)
	, m_log(log)
	, m_index(index)
	{}

	void OnTime()
	{
		m_timer_manager->AddEvent(m_interval, this);
		m_log->Save(m_index);
	}

	void Free(){}

private:
	TimerManager	*m_timer_manager;
	Log 			*m_log;
	unsigned short 	m_index;
	unsigned short 	m_interval;
};


Log::Log(ThreadManager *manager, int log_num, const LogMsg::LogRegister reg[])
: BaseThread(manager, ThreadManager::EXIT_DELAY)
, m_log_num(log_num)
, m_fp(NULL)
, m_timer_manager(New::_TimerManager())
, m_mysql(
CenterConfig::Instance().db.ip,
CenterConfig::Instance().db.user.c_str(),
CenterConfig::Instance().db.passwd.c_str(),
CenterConfig::Instance().db.dbname.c_str(),
CenterConfig::Instance().db.port)
{
	m_name = "log";
	m_log_list = new LogItem[m_log_num];
	for (int i = 0; i < m_log_num; ++i)
	{
		m_log_list[reg[i].index].max_num = reg[i].max_num;
		m_log_list[reg[i].index].format = reg[i].format;
		m_log_list[reg[i].index].base += "INSERT INTO ";
		m_log_list[reg[i].index].base += reg[i].name;
		m_log_list[reg[i].index].base += " ";
		m_log_list[reg[i].index].base += reg[i].fields;
		m_log_list[reg[i].index].base += " VALUE ";
		m_log_list[reg[i].index].logs = m_log_list[reg[i].index].base;
		m_timer_manager->AddEvent(reg[i].interval, new LogTimeEvent(m_timer_manager, this, reg[i].index));
	}
	SetSleepTime(20);
}

Log::~Log()
{
	if (m_fp != NULL)
	{
		fclose(m_fp);
	}
	delete[] m_log_list;
	delete m_timer_manager;
}

bool Log::Init()
{
	std::string path = Function::WorkDir() + "log/";
#ifdef __unix
	if (mkdir(path.c_str(), 0777) != 0)
	{
		Function::Error("can not create log dir %s", path.c_str());
		return false;
	}
	;
#endif
	time_t t = time(NULL);
	char logname[32];
	strftime(logname, sizeof(logname), "%Y%m%d.log", localtime(&t));
	path += logname;
	m_fp = fopen(path.c_str(), "a+");
	if (m_fp == NULL)
	{
		Function::Error("can not create log file %s", path.c_str());
		return false;
	}
	m_timer_manager->AddEvent(5, new LogTimeEvent(m_timer_manager, this, m_log_num));
	return true;
}

bool Log::Run()
{
	return m_timer_manager->Update(time(NULL));
}

void Log::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case LogMsg::LM_REGISTER:
		Register((LogMsg::LogRegister *)data);
		break;
	case LogMsg::LM_WRITE_FILE_ERROR:
		WriteFile(len, data, "%Y%m%d %H:%M:%S ERROR:");
		break;
	case LogMsg::LM_WRITE_FILE_INFO:
		WriteFile(len, data, "%Y%m%d %H:%M:%S INFO :");
		break;
	case LogMsg::LM_WRITE_DB:
		WriteDB(len, data);
		break;
	default:
		break;
	}
}


void Log::Register(LogMsg::LogRegister *data)
{
	if (data->index >= m_log_num)
	{
		Function::Info("log index error %d", data->index);
		return;
	}

	if (m_log_list[data->index].base != "")
	{
		Function::Info("log index is repeat %d\n", data->index);
		return;
	}

	m_log_list[data->index].base += "INSERT INTO ";
	m_log_list[data->index].base += data->name;
	m_log_list[data->index].base += " (rid,log) VALUE ";
	m_log_list[data->index].logs = m_log_list[data->index].base;
}

void Log::WriteDB(int len, const char *data)
{
	LogDB *msg = (LogDB *)data;
	std::string log;
	msg->Do(log, m_log_list[msg->index].format.c_str());
	m_log_list[msg->index].logs = m_log_list[msg->index].logs + log + ",";
	delete msg;
}

void Log::WriteFile(int len, const char *data, const char *format)
{
	if (len > 0)
	{
		time_t t = time(NULL);
		char buffer[64];
		strftime(buffer, sizeof(buffer), format, localtime(&t));
		m_log_file.logs += buffer;
		m_log_file.logs += data;
		m_log_file.logs += '\n';
		if (++m_log_file.num > 100)
		{
			Save(m_log_num);
		}
	}
}

void Log::Save(unsigned short index)
{
	if (index < m_log_num)
	{
		if (m_log_list[index].base.size() > 0 && m_log_list[index].logs.size() > m_log_list[index].base.size())
		{
			m_log_list[index].logs.replace(m_log_list[index].logs.size() - 1, 1, ";");
			if (mysql_query(m_mysql.GetMysql(), m_log_list[index].logs.c_str()) != 0)
	        {
	        	// todo 写文本日志
				Function::Info("%s error %s", m_log_list[index].base.c_str(), mysql_error(m_mysql.GetMysql()));
	        }
			m_log_list[index].logs = m_log_list[index].base;
	         m_log_list[index].cur_num = 0;
		}
	}
	else if (index == m_log_num && m_log_file.logs.size() > 0)
	{
		fwrite(m_log_file.logs.c_str(), m_log_file.logs.size(), 1, m_fp);
		fflush(m_fp);
		m_log_file.logs = "";
		m_log_file.num = 0;
	}
}

EXPORT Log * New::_Log(ThreadManager *manager, int log_num, const LogMsg::LogRegister reg[])
{
	return new Log(manager, log_num, reg);
}
