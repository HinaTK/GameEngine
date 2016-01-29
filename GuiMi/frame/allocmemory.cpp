
#include "lib/include/common/memorypool.h"
#include "scene/observer.h"
#include "scene/scene.h"
#include "obj/role.h"

REGISTER_MEMORYPOOL(gamememorypool, Observer, 128);
REGISTER_MEMORYPOOL(gamememorypool, Scene, 16);
REGISTER_MEMORYPOOL(gamememorypool, Role, 128);