#pragma once

#include "scene.h"

namespace adonai 
{
    class Stage_1
    {       
        private:
            Player* _player;
        public:
            Dungeon(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}