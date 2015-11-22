
#include <stdio.h>
#include "gameframe.h"
#include "common/commonfunction.h"


int main()
{
	if (!NewFrame::Instance().InitConfig())
	{
		Function::WindowsPause();
		return 0;
	}

	NewFrame::Instance().Run();
	Function::WindowsPause();

	return 0;
}