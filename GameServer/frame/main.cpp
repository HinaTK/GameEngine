
#include <stdio.h>
#include "gameframe.h"
#include "common/commonfunction.h"


int main()
{
	if (!GameFrame::Instance().InitConfig())
	{
		Function::WindowsPause();
		return 0;
	}

	GameFrame::Instance().Run();
	Function::WindowsPause();

	return 0;
}