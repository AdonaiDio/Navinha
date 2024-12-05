#pragma once

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_rect.h"
#include "bn_vector.h"
#include "bn_display.h"
#include "bn_sprite_actions.h"
#include "bn_log.h"
#include "bn_sprite_item.h"

#include "utility.h"

#include "e_direction.h"

namespace adonai
{
    class Enemy;
    // extern bn::vector<Enemy*, 20> ntt_enemies;


    enum Shot_State{ //--sem uso--
        NONE,
        SHOOTING
    };

    class Shot
    {
        protected:
            bn::fixed_point _pos;
            bn::sprite_ptr _sprite;
            bn::rect _col;
            int velocity; //era const


        public:
            Shot( const bn::sprite_item& sprite_item, 
                  const bn::fixed_point& initial_position,
                  const bn::rect col = bn::rect{0,0,2,2},
                  const int velocity = 1 )
                :
                _sprite(sprite_item.create_sprite(bn::fixed_point(bn::display::width()+8,0))),
                _pos(initial_position),
                velocity(velocity){};
            ~Shot(){};
            void copy_Shot(const Shot &shot){
                _pos = shot._pos;
                _col = shot._col;
                velocity = shot.velocity;
            };

            // Shot_State _state;

            virtual bn::fixed_point pos() = 0;
            virtual void pos(bn::fixed_point position) = 0;
            virtual bn::sprite_ptr sprite() = 0;
            virtual void sprite(bn::sprite_ptr sprite) = 0;
            virtual bn::rect col() = 0;
            virtual void col(bn::rect collision) = 0;

            virtual void move_forward() = 0;
            // virtual void move_forward(bn::fixed_point point_direction) = 0;
            virtual bool check_collision() = 0;
    };
    
}
