#pragma once
//butano
#include "bn_log.h"
//assets
//#include <bn_sprite_items_.h>
//my code
#include "../include/utility.h"
#include "enemy.h"
//this interface
#include "i_script.hpp"

namespace adonai {
    class Move_Test_Script : public I_Script<Enemy>{
        private:
        
        public:
            void start(Enemy* e) override
            {
            };
            
            void update(Enemy* e) override
            {
                e->pos(move_towards(e->pos(), e->pos()+bn::fixed_point(-1,0), e->velocity()));
            };
    };
} 