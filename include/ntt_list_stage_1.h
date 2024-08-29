#pragma once

#include "bn_vector.h"

#include "enemy.h"
#include "player.h"

namespace adonai
{
    namespace GLOBALS
    {
        Player* global_player;
        
    }
    
    bn::vector<Enemy*, 20> ntt_enemies;

}
    