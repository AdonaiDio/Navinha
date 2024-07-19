#pragma once

#include "bn_fixed_point.h"
#include "bn_sprites.h"
#include "bn_sprite_animate_actions.h"

#include "bn_sprite_items_explosion.h"


//a ideia é só spawnar a explosão(animada) quando um ator exlplodir
//depois se alto destruir
namespace adonai
{
    struct Explosion_FX
    {
        private:
            bn::fixed_point _pos;
            bn::sprite_ptr _sprite;
        public:
            Explosion_FX(bn::fixed_point& pos);
            ~Explosion_FX();

            bn::sprite_animate_action<5> _explosion_anim = bn::create_sprite_animate_action_once(
                _sprite,
                0,
                bn::sprite_items::explosion.tiles_item(),
                0,0,0,0,0
            );
            bn::sprite_ptr sprite();

            void update();
    };
}

