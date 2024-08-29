#pragma once

#include "bn_log.h"

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_rect.h"
#include "bn_sprite_ptr.h"
#include <bn_sprite_palette_ptr.h>

#include "bn_sprite_palette_items_feedback_palette.h"

#include "explosion_fx.h"

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
            const bn::fixed _velocity = 1;
            
            int hit_feedback_duration = 0;
            bn::fixed intensity = 1;
            Explosion_FX* explosion;

        public:
            Actor(  bn::sprite_item sprite_item, 
                    bn::fixed x, bn::fixed y, 
                    bn::sprite_item shot_sprite_item, 
                    int max_hp = 1) :
                    _sprite(sprite_item.create_sprite(x,y)),
                    _sprite_clone(sprite_item.create_sprite(x,y)),
                    _pos(x,y),
                    _hp(max_hp)
                {
                    _sprite_clone.set_z_order(-1);
                    _sprite_clone.set_visible(false);
                    _sprite_clone.set_palette(bn::sprite_palette_items::feedback_palette);
                    BN_LOG("Actor constructor: FINISHED");
                };
            ~Actor() = default;

            bool wait_to_destroy = false;


            bn::fixed_point pos()                   { return _pos; }
            void pos(bn::fixed_point position)  { _pos = position; }
            bn::rect col()                          { return _col; }
            bn::sprite_ptr sprite()              { return _sprite; }
            int hp()                                 { return _hp; }
            void hp(int new_value)              { _hp = new_value; }
            constexpr bn::fixed velocity()               { return _velocity; }

            virtual void hit_feedback();
            virtual void receive_hit(const int i);
            virtual void explode();
            
            virtual void update_collider();
            virtual void update();
    };
}
