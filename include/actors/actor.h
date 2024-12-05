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
            
            // extras   <<< OBS: Povavelmente usarei uma lista na cena em STACK para acessar uma explosao e hit_fx disponível.
            // Explosion_FX* explosion; //jogar na cena
            Explosion_FX explosion = Explosion_FX();
            bool is_hitting = false;
            bn::sprite_palette_ptr hit_palette;
            bn::fixed hit_color_intensity = 1;
            int hit_feedback_duration = 0;

        public:

            Actor(  bn::sprite_item sprite_item,
                    bn::fixed_point position = {0,0},
                    int max_hp = 1) :
                    _sprite(sprite_item.create_sprite(position)),
                    _sprite_item(sprite_item),
                    _pos(position),
                    _hp(max_hp),
                    hit_palette(_sprite.palette())
                {
                    // hit_sprite.set_visible(false);
            BN_LOG("Actor-> Usados: ", bn::sprites::used_items_count());
            BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
            BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            BN_LOG("Actor constructor: FINISHED");
                };
            void copy_Actor(const Actor &actor){
                _sprite = actor._sprite_item.create_sprite();
                _sprite_item = actor._sprite_item;
                _pos = actor._pos;
                _col = actor._col;
                _hp = actor._hp;
                _velocity = actor._velocity;
                hit_palette = actor._sprite_item.palette_item().create_new_palette();
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
                hit_feedback_duration = 15;
                hit_palette = _sprite_item.palette_item().create_new_palette();
                _sprite.set_palette(hit_palette);
                bn::sound_items::hit.play();
                is_hitting = true;
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
                // explosion = new Explosion_FX(_pos);
                explosion.init_explosion(_pos);
                BN_LOG("explosion Usados: ", bn::sprites::used_items_count());
                BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
                BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            };
            
            void update_collider();
            void update_scripts();
            void update_hit_fx(){
                if(!is_hitting) return;
                if (hit_feedback_duration > 0)
                {
                    // bn::sprite_palette_ptr hit_palette = _sprite.palette();
                    //muda as cores para as cores do enemy que está levando hit já que a palette é compartilhada
                    for (int i = 0; i < _sprite.palette().colors().size(); i++)
                    {
                        hit_palette.set_color(i,_sprite.palette().colors().at(i));
                    }
                    
                    if (hit_feedback_duration % 15 == 0) //se for divisível por 15
                    {
                        hit_palette.set_fade(bn::colors::white, hit_color_intensity);
                        hit_color_intensity = 1;
                    }
                    else
                    {
                        hit_color_intensity = bn::clamp((bn::fixed(-0.1) + hit_color_intensity), bn::fixed(0), bn::fixed(1));
                        hit_palette.set_fade(bn::colors::white, hit_color_intensity);
                    }
                    hit_feedback_duration--;
                    if(hit_feedback_duration == 0){
                        _sprite.set_palette(_sprite_item.palette_item());
                        is_hitting = false;
                    }
                } 
        _sprite.set_position(_pos);
            };
            void update();
    };
}
