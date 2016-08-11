
#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include "lib/include/base/function.h"

#define GAME_MAIN(CLASS)\
	int main(){\
		if (!CLASS::Instance().Init()) { \
			Function::WindowsPause(); \
			return 0; \
		}\
		Function::Info("Init %s success", #CLASS); \
		if (!CLASS::Instance().Start()){ \
			Function::Info("Start %s fail", #CLASS); \
		}\
		return 0;\
	}

#endif