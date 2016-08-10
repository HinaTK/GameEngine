
#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include "lib/include/base/function.h"

#define GAME_MAIN(CLASS)\
	int main(){\
		if (!CLASS::Instance().Init()) { \
			Function::WindowsPause(); \
			return 0; \
		}\
		Function::Info("init %s success", #CLASS); \
		if (!CLASS::Instance().Start()){ \
			printf("start %s fail\n", #CLASS); \
		}\
		return 0;\
	}

#endif