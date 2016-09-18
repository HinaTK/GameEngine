
#ifndef LOGIN_SCENE_THREAD_ID_H
#define LOGIN_SCENE_THREAD_ID_H

#include "lib/include/thread/threadsysid.h"

namespace LoginSceneTID
{
	enum
	{
		REG_ROLE = ThreadSysID::TSID_MAX_ID,
		LOAD_ROLE
	};
}

#endif
