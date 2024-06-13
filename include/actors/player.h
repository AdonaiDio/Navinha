#pragma once

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_list.h"

#include "shoot.h"

#include "bn_sprite_items_nova.h"

namespace adonai
{
    class Player
    {
        private:
            bn::sprite_ptr _sprite;
            bn::fixed_point _pos;
        public:
            // TODO: futuramente com mais tiros, pode ser que passar sprite não seja a melhor solução. 
            // Organizar uma lista de tiros em forma de Enum pode ser o melhor caminho.
            bn::array<adonai::Shoot, 15> _shoots;
            //bn::list<adonai::Shoot, 15> _shoots;

            // Player(bn::sprite_ptr sprite, bn::sprite_ptr _shoot_sprite);

            Player(bn::sprite_ptr sprite, bn::sprite_item shoot_sprite_item);

            bn::sprite_ptr sprite();

            bn::fixed_point pos();
            void set_pos(bn::fixed_point location);

            void spawn(bn::fixed_point location);

            void set_shoot_sprite(bn::sprite_ptr shoot_sprite); 

            void update_sprite_position(adonai::Player& player);
    };

}