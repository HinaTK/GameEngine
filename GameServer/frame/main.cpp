
#include "game.h"
#include "lib/include/common/function.h"


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