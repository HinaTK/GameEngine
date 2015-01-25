
#include "commonfunction.h"
#include "commonvariable.h"

void Function::WindowsPause()
{
#ifdef WIN32
	system("pause");
#endif
}

std::string Function::WorkDir()
{
	std::string strPath = "";
#ifdef WIN32
	char exeFullPath[MAX_PATH] = {0}; // Full path
	GetModuleFileNameA(NULL, exeFullPath, MAX_PATH);

	strPath = std::string(exeFullPath);    // Get full path of the file
	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos);  // Return the directory without the file name
#endif
#ifdef __unix
	return strPath;
#endif // __unix

}

unsigned long Function::GetThreadID()
{
#ifdef WIN32
	return GetCurrentThreadId();
#endif
	return 0;
}

const char * Function::GetServerName(unsigned int type)
{
	switch (type)
	{
	case DATABASE_SERVER:
		return "DatabaseServer";
	case LOGIN_SERVER:
		return "LoginServer";
	case GAME_SERVER:
		return "GameServer";
	case GATEWAY_SERVER:
		return "GatewayServer";
	default:
		break;
	}
	return NULL;
}
