#pragma once

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

namespace adonai
{
    class Player
    {
        private:
            bn::sprite_ptr _sprite;
            //bn::fixed _dx;
            //bn::fixed _dy;
            bn::fixed_point _pos;

        public:
            Player(bn::sprite_ptr sprite);
            bn::fixed_point pos();

    };

}