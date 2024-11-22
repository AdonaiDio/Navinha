#pragma once

#include "bn_log.h"

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_rect.h"
#include "bn_sprite_ptr.h"
#include <bn_sprite_palette_ptr.h>
#include "bn_color.h"
#include "bn_colors.h"
#include "bn_sound_items.h"

#include "bn_sprite_palette_items_feedback_palette.h"

#include "explosion_fx.h"
#include "hit_fx.h"

#include "i_script.hpp"

#include "enemy.h"

namespace adonai
{
    template <class T>
    class Actor
    {
        protected:
            bn::sprite_ptr _sprite;
            bn::sprite_item _sprite_item;
            bn::fixed_point _pos;
            bn::rect _col = bn::rect( 0, 0, 0, 0 );

            int _hp = 1;
            bn::fixed _velocity = 1;
            
            // extras
            Explosion_FX* explosion;
            Hit_FX* hit_fx;
            bool is_hitting = false;

        public:
            Actor(  bn::sprite_item sprite_item,
                    bn::fixed_point position = {0,0},
                    int max_hp = 1) :
                    _sprite(sprite_item.create_sprite(position)),
                    _sprite_item(sprite_item),
                    _pos(position),
                    _hp(max_hp)
                {
            BN_LOG("Actor-> Usados: ", bn::sprites::used_items_count());
            BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
            BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            BN_LOG("Actor constructor: FINISHED");
                };
            ~Actor() = default;

            // lugar para guardar os scripts associados ao enemy
            bn::vector<I_Script<T>*, 12> _scripts;

            bool wait_to_destroy = false;


            bn::fixed_point pos()                               { return _pos; }
            void pos(bn::fixed_point position)              { _pos = position; }
            void pos(bn::fixed x, bn::fixed y)  { _pos = bn::fixed_point(x,y); }
            void pos_x(bn::fixed x)     { _pos = bn::fixed_point(x, _pos.y()); }
            void pos_y(bn::fixed y)     { _pos = bn::fixed_point(_pos.x(), y); }
            bn::rect col()                                      { return _col; }
            void col(bn::rect new_value)                   { _col = new_value; }
            bn::sprite_ptr sprite()                          { return _sprite; }
            void sprite(bn::sprite_ptr sprite)             { _sprite = sprite; }
            int hp()                                             { return _hp; }
            void hp(int new_value)                          { _hp = new_value; }
            bn::fixed velocity()                           { return _velocity; }
            void velocity(bn::fixed new_vel)            { _velocity = new_vel; }

            //--methods--
            void hit_feedback()
            {
                is_hitting = true;
                hit_fx = new Hit_FX(_pos, _sprite_item, is_hitting);
                BN_LOG("is hitting: ", is_hitting);
                BN_LOG("hitFX Usados: ", bn::sprites::used_items_count());
                BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
                BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            };

            void receive_hit()
            {
                if (_hp <= 0) {return;}//assegurar que não vai receber hit se já estiver morto
                _hp -= 1;
                if (_hp > 0) {
                    bn::sound_items::hit.play();
                    if(!is_hitting){
                        hit_feedback();
                    }
                    return;
                }
                wait_to_destroy = true;
                explode();
            };

            void explode()
            {
                _sprite.set_visible(false);
                explosion = new Explosion_FX(_pos);
                BN_LOG("explosion Usados: ", bn::sprites::used_items_count());
                BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
                BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            };
            
            void update_collider();
            void update_scripts();
            void update();
    };
}
