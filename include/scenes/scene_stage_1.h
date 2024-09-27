#pragma once

#include "scene.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"


namespace adonai 
{
    class Player;
    
    class Stage_1
    {       
        private:
            Player* _player;
            
        public:
            Stage_1(Player& player);
            Scene execute(bn::fixed_point spawn);
            // bn::span<bn::color> bg_palette_hbe( bn::regular_bg_ptr r_bg );

            // update todos os inimigos na cena
            void update_all_enemies();
            // update todos os tiros na cena
            void update_all_shoots();
    };
}