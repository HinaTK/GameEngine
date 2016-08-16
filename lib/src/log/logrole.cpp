
#include "logrole.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/base/function.h"

LogRole::LogRole(ThreadManager *manager, int log_num, LogDBMsg::LogRegister *reg)
: BaseThread(manager, NULL, ThreadManager::EXIT_DELAY)
, m_log_num(log_num)
, m_next_time(time(NULL) + SAVE_INTERVAL)
, m_mysql(
CenterConfig::Instance().db.ip,
CenterConfig::Instance().db.user.c_str(),
CenterConfig::Instance().db.passwd.c_str(),
CenterConfig::Instance().db.dbname.c_str(),
CenterConfig::Instance().db.port)
{
	m_log_list = new LogItem[m_log_num];
	for (int i = 0; i < m_log_num; ++i)
	{
		m_log_list[reg[i].index].default += "INSERT INTO ";
		m_log_list[reg[i].index].default += reg[i].name;
		m_log_list[reg[i].index].default += " (rid,log) VALUE ";
		m_log_list[reg[i].index].logs = m_log_list[reg[i].index].default;
	}
	SetSleepTime(20);
}

LogRole::~LogRole()
{
	delete[] m_log_list;
}

bool LogRole::Run()
{
	time_t now = time(NULL);
	if (now > m_next_time)
	{
		for (int i = 0; i < m_log_num; ++i)
		{
			if (m_log_list[i].default.size() > 0 && m_log_list[i].logs.size() > m_log_list[i].default.size())
			{
				m_log_list[i].logs.replace(m_log_list[i].logs.size() - 1, 1, ");");
				int ret = mysql_query(m_mysql.GetMysql(), m_log_list[i].logs.c_str());//查询
		        if(ret != 0)
		        {
		        	// todo 写文本日志
		            Function::Info("save role log error %s\n",mysql_error(m_mysql.GetMysql()));
		        }
		         m_log_list[i].logs = m_log_list[i].default;
			}
		}
		m_next_time = now;
	}
	
	return false;
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
	if (len <= LogDBMsg::LOG_WRITE_LEN)
	{
		return;
	}

	LogDBMsg::LogWrite *lw = (LogDBMsg::LogWrite *)data;
	int data_len = len - LogDBMsg::LOG_WRITE_LEN;
}

void LogRole::RoleWrite(int len, const char *data)
{
	if (len <= LogDBMsg::LOG_ROLE_WRITE_LEN)
	{
		return;
	}

	LogDBMsg::LogRoleWrite *lw = (LogDBMsg::LogRoleWrite *)data;
	if (lw->index >= m_log_num || m_log_list[lw->index].default.size() > 0)
	{
		return;
	}
	
	int data_len = len - LogDBMsg::LOG_ROLE_WRITE_LEN;
	char *log = (char *)(data + LogDBMsg::LOG_ROLE_WRITE_LEN);
	log[data_len - 1] = 0;
	static char str_val[32];
#if (defined _WIN32) || (defined _WIN64)
	sprintf(str_val,"(%I64d,",lw->role_id);
#elif
	sprintf(str_val,"(%lld,",lw->role_id);	
#endif	
	
	m_log_list[lw->index].logs = m_log_list[lw->index].logs + str_val + log + "),";
}

int LogRole::MakeLog(unsigned short index, RoleID role_id, char *buf, char *format, ...)
{
	va_list args; 
	va_start(args, format); 
	int ret = vsprintf(buf, format, args);
	va_end(args); 
	if (ret > 0)
	{
		return LogDBMsg::LOG_ROLE_WRITE_LEN + ret;
	}
	return ret;
}