#pragma once
#include "bn_core.h"

namespace adonai
{
    enum SpawnEnemy_State: int8_t{
        SPAWNENEMY_NONE_STATE=0,
        SPAWNENEMY_SPAWN_STATE=1,
        SPAWNENEMY_REPOSITIONING_STATE=2,
        SPAWNENEMY_ATTACKING_STATE=3,
        SPAWNENEMY_OUTSIDE_STATE=4,
        SPAWNENEMY_DEAD_STATE=5,
    };
} // namespace adonai
