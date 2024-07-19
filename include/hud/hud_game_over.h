#pragma once

#include "bn_array.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_game_over.h"

namespace adonai
{
    struct hud_game_over
    {
        private:
            bn::fixed_point _pos;
        public:
            hud_game_over(int x, int y);
            ~hud_game_over();

            void pos(int x, int y);
            bn::fixed_point pos();

            bn::array<bn::sprite_ptr,3> _sprites;
            
            void update();
    };
    
}