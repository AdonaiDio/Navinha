#pragma once

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spaceship_3.h"


namespace adonai
{
    class Obj{
        private:
            bn::sprite_ptr _sprite;
        public:
        Obj(bn::sprite_item sprite_item = bn::sprite_items::spaceship_3);
    };
} // namespace adonai
