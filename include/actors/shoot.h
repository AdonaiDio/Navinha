#pragma once

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_rect.h"
#include "bn_vector.h"

#include "e_direction.h"
#include "e_tags.h"

namespace adonai
{
    class Enemy;
    extern bn::vector<Enemy*, 20> ntt_enemies;

    enum Shoot_State{
        NONE,
        SHOOTING
    };

    struct Shoot
    {
        private:
            bn::fixed_point _pos;
            Direction _dir;
            bn::sprite_ptr _sprite;
            bn::rect _col;
            Tag _owner_tag;

            //TODO: testar até onde da para aumentar sem sentir muito delay
            const int frame_frequency = 2;
            int frame_counter = 0;

        public:
            Shoot(  const bn::sprite_item& sprite_item, 
                    const bn::fixed_point& initial_position, 
                    const Direction& direction,
                    const Tag& owner_tag);
            ~Shoot();

            Shoot_State _state;

            bn::fixed_point pos();
            void set_pos(bn::fixed_point position);
            Direction dir();
            bn::sprite_ptr sprite();
            bn::rect col();
            Tag owner_tag();
            bool _can_col;//can collide

            void set_sprite(bn::sprite_ptr sprite);

            const int direction_axis_x();

            void Move_Forward();
            bool check_collision();
    };
    
}
