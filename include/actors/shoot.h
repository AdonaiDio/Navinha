#pragma once

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "e_direction.h"
namespace adonai
{
    enum Shoot_State{
        NONE,
        SHOOTING
    };

    struct Shoot
    {
        private:
            bn::fixed_point _pos;
            adonai::Direction _dir;
            bn::sprite_ptr _sprite;

        public:
            // Shoot(
            //     bn::sprite_ptr sprite,
            //     bn::fixed_point initial_position,
            //     adonai::Direction direction
            // );
            Shoot(bn::sprite_item sprite_item, bn::fixed_point initial_position, adonai::Direction direction);
            ~Shoot();

            adonai::Shoot_State _state;

            bn::fixed_point pos();
            void set_pos(bn::fixed_point position);
            adonai::Direction dir();
            bn::sprite_ptr sprite();

            void set_sprite(bn::sprite_ptr sprite);

            const int direction_axis_x();

            void Move_Forward();
    };
    
}
