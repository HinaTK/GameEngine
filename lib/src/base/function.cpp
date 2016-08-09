
#include "function.h"
#include "common/socketdef.h"
#include "common/protocol/messageheader.h"

void Function::WindowsPause()
{
#if (defined _WIN32) || (defined _WIN64)
	system("pause");
#endif
}

std::string Function::WorkDir()
{
#if (defined _WIN32) || (defined _WIN64)
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
#if (defined _WIN32) || (defined _WIN64)
	return GetCurrentThreadId();
#endif
	return 0;
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

void Function::Info(char *str, ...)
{
	time_t t = time(NULL);
	char buffer[64];
	strftime(buffer, sizeof(buffer), "%Y%m%d %H:%M:%S ", localtime(&t));
	printf(buffer);
	va_list args; 
	va_start(args, str);
	vprintf(str, args);
	va_end(args); 
	printf("\n");
}
