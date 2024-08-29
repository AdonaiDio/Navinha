#pragma once

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_rect.h"
#include "bn_vector.h"
#include "bn_display.h"
#include "bn_sprite_actions.h"
#include "bn_log.h"
#include "bn_sprite_item.h"


#include "e_direction.h"

namespace adonai
{
    class Enemy;
    extern bn::vector<Enemy*, 20> ntt_enemies;


    enum Shot_State{
        NONE,
        SHOOTING
    };

    class Shot
    {
        protected:
            bn::fixed_point _pos;
            bn::sprite_ptr _sprite;
            bn::rect _col;

            const int velocity = 3;

        public:
            Shot(  const bn::sprite_item& sprite_item, 
                    const bn::fixed_point& initial_position)
                :
                _sprite(sprite_item.create_sprite(bn::fixed_point(bn::display::width()+8,0))),
                _pos(initial_position){};
            ~Shot(){};

            Shot_State _state;

            virtual bn::fixed_point pos() = 0;
            virtual void pos(bn::fixed_point position) = 0;
            virtual bn::sprite_ptr sprite() = 0;
            virtual void sprite(bn::sprite_ptr sprite) = 0;
            virtual bn::rect col() = 0;

            virtual void Move_Forward() = 0;
            virtual bool check_collision() = 0;
    };
    
}
