#pragma once

#include "bn_fixed_point.h"
#include "bn_sprites.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"


//a ideia é só spawnar o hit(animada) quando um ator for atingido
//depois se auto-destruir
namespace adonai
{
    struct Hit_FX
    {
        private:
            bn::fixed_point& _pos; //posição de quem recebe hit 
            bn::sprite_ptr _sprite;
            bn::sprite_palette_ptr _palette;
            bn::fixed intensity = 1;
            bool& _is_hitting;
        public:
            Hit_FX( bn::fixed_point& pos, bn::sprite_item sprite_item,
                    int sprite_index, bool& is_hitting);
            Hit_FX( bn::fixed_point& pos, bn::sprite_item sprite_item,
                    bool& is_hitting);
            ~Hit_FX();

            int hit_feedback_duration = 15;
            bn::sprite_ptr sprite();
            void update();
    };
}

