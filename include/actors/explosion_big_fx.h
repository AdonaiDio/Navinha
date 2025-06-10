#pragma once

#include "bn_fixed_point.h"
#include "bn_sprites.h"
#include "bn_sprite_animate_actions.h"

#include "bn_sprite_items_explosion_big.h"


//a ideia é só spawnar a explosão(animada) quando um ator exlplodir
//depois se alto destruir
namespace adonai
{
    struct Explosion_Big_FX
    {
        private:
        public:
            Explosion_Big_FX();

            bn::sprite_ptr _sprite;

            bool available = true;
            bool is_exploding = false;

            bn::sprite_animate_action<6> _explosion_anim = bn::create_sprite_animate_action_once(
                _sprite,
                0,
                bn::sprite_items::explosion_big.tiles_item(),
                0,0,0,0,0,0
            );

            void init_explosion(const bn::fixed_point pos);

            void update();
    };
}

