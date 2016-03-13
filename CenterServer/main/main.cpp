
#include "center.h"
#include "common/commonfunction.h"


int main()
{
	if (!Center::Instance().Init())
	{
		Function::WindowsPause();
		return 0;
	}

	Center::Instance().Start();

	return 0;
}