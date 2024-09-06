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

#include "enemy.h"

namespace adonai
{
    class Actor
    {
        protected:
            bn::sprite_ptr _sprite;
            bn::sprite_ptr _sprite_clone;
            bn::fixed_point _pos;
            bn::rect _col = bn::rect( 0, 0, 0, 0 );

            int _hp;
            bn::fixed _velocity = 1;
            
            int hit_feedback_duration = 0;
            bn::fixed intensity = 1;
            Explosion_FX* explosion;

        public:
            Actor(  bn::sprite_item sprite_item,
                    bn::fixed_point position,
                    int max_hp = 1) :
                    _sprite(sprite_item.create_sprite(position)),
                    _sprite_clone(sprite_item.create_sprite(position)),
                    _pos(position),
                    _hp(max_hp)
                {
                    _sprite_clone.set_z_order(-1);
                    _sprite_clone.set_visible(false);
                    _sprite_clone.set_palette(bn::sprite_palette_items::feedback_palette);
                    //BN_LOG("Actor constructor: FINISHED");
                };
            ~Actor() = default;

            bool wait_to_destroy = false;


            bn::fixed_point pos()                   { return _pos; }
            void pos(bn::fixed_point position)  { _pos = position; }
            bn::rect col()                          { return _col; }
            bn::sprite_ptr sprite()              { return _sprite; }
            int hp()                                 { return _hp; }
            void hp(int new_value)              { _hp = new_value; }
            bn::fixed velocity()               { return _velocity; }
            void velocity(bn::fixed new_vel){ _velocity = new_vel; }

            //--methods--
            void hit_feedback()
            {
                if (hit_feedback_duration > 0)
                {
                    //!!! Codigo RUIM. Paleta trocando para todos os tipos de enemy !!!
                    _sprite_clone.set_visible(true);
                    bn::sprite_palette_ptr clone_palette = _sprite_clone.palette();
                    //muda as cores para as cores do enemy que está levando hit já que a palette é compartilhada
                    for (int i = 0; i < _sprite.palette().colors().size(); i++)
                    {
                        clone_palette.set_color(i,_sprite.palette().colors().at(i));
                    }
                    
                    if (hit_feedback_duration % 15 == 0) //se for divisível por 15
                    {
                        clone_palette.set_fade(bn::colors::white, intensity);
                        intensity = 1;
                    }
                    else
                    {
                        intensity = bn::clamp((bn::fixed(-0.1) + intensity), bn::fixed(0), bn::fixed(1));
                        clone_palette.set_fade(bn::colors::white, intensity);
                    }
                    hit_feedback_duration--;
                    if(hit_feedback_duration == 0){
                        _sprite_clone.set_visible(false);
                    }
                }        
            };

            void receive_hit(const int index)
            {
                if (_hp <= 0) {return;}//assegurar que não vai receber hit se já estiver morto
                _hp -= 1;
                if (_hp > 0) {
                    bn::sound_items::hit.play();
                    hit_feedback_duration = 15; //frames de duração do hit_feedback
                    return;
                }
                wait_to_destroy = true;
                explode();
            };

            void explode()
            {
                _sprite.set_visible(false);
                _sprite_clone.set_visible(false);
                explosion = new Explosion_FX(_pos);
            };
            
            void update_collider();
            void update();
    };
}
