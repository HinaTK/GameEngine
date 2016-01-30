
#include <stdio.h>
#include "gameframe.h"
#include "common/commonfunction.h"


int main()
{
	if (!NewFrame::Instance().Init())
	{
		Function::WindowsPause();
		return 0;
	}

	NewFrame::Instance().Start();
	
	return 0;
}