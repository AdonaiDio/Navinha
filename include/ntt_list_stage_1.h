#pragma once

#include "bn_vector.h"

#include "enemy.h"
#include "shot_enemy.h"
#include "player.h"

namespace adonai
{
    namespace GLOBALS
    {
        Player* global_player;
        
    }
    
    bn::vector<Enemy*, 28> ntt_enemies;
    bn::vector<Shot_Enemy*, 60> ntt_shots;
}
    