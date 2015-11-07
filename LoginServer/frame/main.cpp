
#include "loginframe.h"
#include "common/commonfunction.h"

int main()
{
	if (!LoginFrame::Instance().InitConfig())
	{
		Function::WindowsPause();
		return 0;
	}

	LoginFrame::Instance().Run();
	Function::WindowsPause();
	return 0;
}
