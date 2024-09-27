#pragma once
//butano
#include "bn_log.h"
#include "bn_display.h"
//assets
//#include <bn_sprite_items_.h>
//my code
#include "../include/utility.h"
#include "enemy.h"
//this interface
#include "i_script.hpp"

namespace adonai {
    class Move_And_Destroy_Script : public I_Script<Enemy>{
        public:
        void start(Enemy* e) override
        {
        };
        
        void update(Enemy* e) override
        {
            
            if(e == nullptr){return;}
            if(OutOfScreen(e)){
                e->just_delete_this();
                return;
            }
            e->pos(move_towards(e->pos(), e->pos()+bn::fixed_point(-1,0), e->velocity()));
        };
        
        private:
        bool OutOfScreen(Enemy* e){
            if(e->pos().x() <= (-1 * bn::display::width()/2)-16){
                return true;
            }
            return false;
        }
    };
} 