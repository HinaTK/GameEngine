
#include "module.h"

bool RoleModule::Save()
{
	std::string str;
	if (!Serialize(str))
	{
		return false;
	}

	// todo 做数据保存操作
}