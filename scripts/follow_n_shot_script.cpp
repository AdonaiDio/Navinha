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
    class Follow_N_Shot_Script : public I_Script<Enemy>{
        private:
        bn::fixed min_x = 0;
        bn::fixed max_x = 32;
        // true = min; false = max;
        bool min_max_toggle = true;
        bool is_moving = true;
        
        public:
        void start(Enemy* e) override
        {
            min_max_toggle = true;
        };
        
        void update(Enemy* e) override
        {
            Move_to_x_range(e);
        };

        void Move_to_x_range(Enemy* e){
            if (min_max_toggle)
            {
                if (e->pos().x() <= min_x)
                {
                    /* code */
                }
                
                e->pos(move_towards(e->pos(), e->pos()+bn::fixed_point(-1,0), e->velocity()));
            }
            else{

            }
            
        }
    };
}