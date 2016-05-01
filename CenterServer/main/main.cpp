
#include "center.h"
#include "lib/include/common/function.h"
#include <windows.h>

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