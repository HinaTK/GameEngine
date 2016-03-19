
#include "gateway.h"
#include "common/commonfunction.h"


int main()
{
	if (!Gateway::Instance().Init())
	{
		Function::WindowsPause();
		return 0;
	}

	Gateway::Instance().Start();

	return 0;
}