#pragma once

#include "bn_log.h"

#include "../include/utility.h"
#include "enemy.h"

#include "i_script.hpp"
namespace adonai
{

class Move_Test_Script : I_Script<Enemy>{
    private:

    public:
        void start(Enemy& e)override
        {
            BN_LOG("START SCRIPT WITH HP: ", e.hp());
        };
        
        void update(Enemy& e) override
        {
            e.pos(move_towards(e.pos(), e.pos()+bn::fixed_point(-1,0), e.velocity()));
        };
};

} 