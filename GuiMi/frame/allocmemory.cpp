
#include "lib/include/common/memorypool.h"
#include "scene/observer.h"
#include "scene/scene.h"

REGISTER_MEMORYPOOL(gamememorypool, Observer, 256);
REGISTER_MEMORYPOOL(gamememorypool, Scene, 16);