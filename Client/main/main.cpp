
#include "client.h"
#include "lib/include/common/function.h"


int main()
{
	if (!Client::Instance().Init())
	{
		Function::WindowsPause();
		return 0;
	}

	Client::Instance().Start();

	return 0;
}