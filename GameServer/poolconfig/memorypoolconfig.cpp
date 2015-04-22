
#include "lib/include/common/memorypool.h"
#include "global/globalvariable.h"
#include "scene/observer.h"
#include "test.h"


REGISTER_MEMORYPOOL(gamememorypool, Test, 64);
REGISTER_MEMORYPOOL(gamememorypool,	Observer, 256);


