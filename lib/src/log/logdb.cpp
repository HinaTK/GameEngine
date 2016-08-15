
#include "logdb.h"
#include "lib/include/common/serverconfig.h"

LogDB::LogDB(ThreadManager *manager, int log_num)
: BaseThread(manager, NULL, ThreadManager::EXIT_DELAY)
, m_log_num(log_num)
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
		m_log_list[i].db_name = "";
	}
	SetSleepTime(20);
}

LogDB::~LogDB()
{
	delete[] m_log_list;
}

bool LogDB::Run()
{
	// todo 
	return false;
}

void LogDB::RecvData(short type, ThreadID sid, int len, const char *data)
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


void LogDB::Register(LogDBMsg::LogRegister *data)
{
	if (data->index >= m_log_num)
	{
		printf("log index error %d\n", data->index);
		return;
	}

	if (m_log_list[data->index].db_name != "")
	{
		printf("log index is repeat %d\n", data->index);
		return;
	}

	m_log_list[data->index].db_name = data->name;
}

void LogDB::Write(int len, const char *data)
{
	if (len <= LogDBMsg::LOG_WRITE_LEN)
	{
		return;
	}

	LogDBMsg::LogWrite *lw = (LogDBMsg::LogWrite *)data;
	int data_len = len - LogDBMsg::LOG_WRITE_LEN;
}

void LogDB::RoleWrite(int len, const char *data)
{
	if (len <= LogDBMsg::LOG_ROLE_WRITE_LEN)
	{
		return;
	}

	LogDBMsg::LogRoleWrite *lw = (LogDBMsg::LogRoleWrite *)data;
	if (lw->index >= m_log_num || m_log_list[lw->index].db_name == "")
	{
		return;
	}
	
	int data_len = len - LogDBMsg::LOG_ROLE_WRITE_LEN;
	char *log = (char *)(data + LogDBMsg::LOG_ROLE_WRITE_LEN);
	log[data_len - 1] = 0;
	m_log_list[lw->index].logs.Push(std::string(log));
}

int LogDB::MakeJson(char *buf, char *format, ...)
{
	va_list args; 
	va_start(args, format); 
	int ret = vsprintf(buf, format, args);
	va_end(args); 
	return ret;
}
