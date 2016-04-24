
#include "function.h"
#include "common/socketdef.h"
#include "common/protocol/messageheader.h"

void Function::WindowsPause()
{
#ifdef WIN32
	system("pause");
#endif
}

std::string Function::WorkDir()
{
#ifdef WIN32
	std::string strPath = "";
	char exeFullPath[MAX_PATH] = {0}; // Full path
	GetModuleFileNameA(NULL, exeFullPath, MAX_PATH);

	strPath = std::string(exeFullPath);    // Get full path of the file
	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos);  // Return the directory without the file name
#endif
#ifdef __unix
	return getcwd(NULL,0);
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

bool Function::ProtocolDecode(const char *buf, unsigned int len)
{
	if (len < sizeof(EProtocol::MessageHeader))
	{
		return false;
	}

	EProtocol::MessageHeader *header = (EProtocol::MessageHeader *)buf;
	const char *message_buf = buf + sizeof(EProtocol::MessageHeader);
	int message_len = (int)(len - sizeof(EProtocol::MessageHeader));

	unsigned int check = 0;
	for (int i = 0; i < message_len; ++i)
	{
		check += (((unsigned int)*(unsigned char *)message_buf) << 16);
		++message_buf;
	}

	return (header->check == check);
}
