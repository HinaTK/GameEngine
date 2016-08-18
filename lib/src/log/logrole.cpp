
#include "logrole.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/base/function.h"

// 同一个线程内，共用LogItem线程安全

class LogTimeEvent : public TimeEvent
{
public:
	LogTimeEvent(TimerManager *timer_manager, LogRole *role, unsigned short index)
	: TimeEvent()
	, m_timer_manager(timer_manager)
	, m_log_role(role)
	, m_index(index)
	{}

	void OnTime()
	{
		m_log_role->Save(m_index);
		m_timer_manager->AddEvent(m_interval, this);
	}

private:
	TimerManager	*m_timer_manager;
	LogRole 		*m_log_role;
	unsigned short 	m_index;
	unsigned short 	m_interval;
};


LogRole::LogRole(ThreadManager *manager, int log_num, const LogDBMsg::LogRegister reg[])
: BaseThread(manager, NULL, ThreadManager::EXIT_DELAY)
, m_log_num(log_num)
, m_timer_manager(New::_TimerManager())
, m_mysql(
CenterConfig::Instance().db.ip,
CenterConfig::Instance().db.user.c_str(),
CenterConfig::Instance().db.passwd.c_str(),
CenterConfig::Instance().db.dbname.c_str(),
CenterConfig::Instance().db.port)
{
	m_name = "log role";
	m_log_list = new LogItem[m_log_num];
	for (int i = 0; i < m_log_num; ++i)
	{
		m_log_list[reg[i].index].max_num = reg[i].max_num;
		m_log_list[reg[i].index].format = reg[i].format;
		m_log_list[reg[i].index].default += "INSERT INTO ";
		m_log_list[reg[i].index].default += reg[i].name;
		m_log_list[reg[i].index].default += " ";
		m_log_list[reg[i].index].default += reg[i].fields;
		m_log_list[reg[i].index].default += " VALUE ";
		m_log_list[reg[i].index].logs = m_log_list[reg[i].index].default;
		m_timer_manager->AddEvent(reg[i].interval, new LogTimeEvent(m_timer_manager, this, reg[i].index));
	}
	SetSleepTime(20);
}

LogRole::~LogRole()
{
	delete[] m_log_list;
	delete m_timer_manager;
}

bool LogRole::Run()
{
	return m_timer_manager->Update(time(NULL));
}

void LogRole::RecvData(short type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case LogDBMsg::LDM_REGISTER:
		Register((LogDBMsg::LogRegister *)data);
		break;
	case LogDBMsg::LDM_WRITE:
		Write(len, data);
		break;
	default:
		break;
	}
}


void LogRole::Register(LogDBMsg::LogRegister *data)
{
	if (data->index >= m_log_num)
	{
		Function::Info("log index error %d", data->index);
		return;
	}

	if (m_log_list[data->index].default != "")
	{
		Function::Info("log index is repeat %d\n", data->index);
		return;
	}

	m_log_list[data->index].default += "INSERT INTO ";
	m_log_list[data->index].default += data->name;
	m_log_list[data->index].default += " (rid,log) VALUE ";
	m_log_list[data->index].logs = m_log_list[data->index].default;
}

void LogRole::Write(int len, const char *data)
{
	LogMsg *msg = (LogMsg *)data;
	std::string log;
	msg->Do(log, m_log_list[msg->index].format.c_str());
	m_log_list[msg->index].logs = m_log_list[msg->index].logs + log + ",";
	delete msg;
}

void LogRole::Save(unsigned short index)
{
	if (index < m_log_num)
	{
		if (m_log_list[index].default.size() > 0 && m_log_list[index].logs.size() > m_log_list[index].default.size())
		{
			m_log_list[index].logs.replace(m_log_list[index].logs.size() - 1, 1, ";");
			if (mysql_query(m_mysql.GetMysql(), m_log_list[index].logs.c_str()) != 0)
	        {
	        	// todo 写文本日志
	            Function::Info("%s error %s", m_log_list[index].default.c_str(), mysql_error(m_mysql.GetMysql()));
	        }
	         m_log_list[index].logs = m_log_list[index].default;
	         m_log_list[index].cur_num = 0;
		}
	}
}

int LogRole::MakeLog(unsigned short index, RoleID role_id, char *buf, char *format, ...)
{
	va_list args; 
	va_start(args, format); 
	int ret = vsprintf(buf + LogDBMsg::LOG_ROLE_WRITE_LEN, format, args);
	va_end(args); 
	if (ret > 0)
	{
		LogDBMsg::LogRoleWrite lw;
		lw.index = index;
		lw.role_id = role_id;
		lw.len = ret;
		memcpy(buf,  &lw, LogDBMsg::LOG_ROLE_WRITE_LEN);
		return LogDBMsg::LOG_ROLE_WRITE_LEN + ret + 1;
	}
	return ret;
}