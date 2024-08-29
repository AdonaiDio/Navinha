#pragma once

#include "scene.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"


namespace adonai 
{
    class Player;
    
    class Test
    {       
        private:
            Player* _player;
        public:
            Test(Player& player);
            Scene execute(bn::fixed_point spawn);
            // bn::span<bn::color> bg_palette_hbe( bn::regular_bg_ptr r_bg );
    };
}