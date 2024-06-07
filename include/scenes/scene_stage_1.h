#pragma once

#include "scene.h"
#include "../actors/player.h"
#include "bn_fixed_point.h"

namespace adonai 
{
    class Stage_1
    {       
        private:
            Player* _player;
        public:
            Stage_1(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}