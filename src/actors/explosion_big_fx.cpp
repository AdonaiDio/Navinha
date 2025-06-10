#include "bn_log.h"
#include "bn_sound_items.h"

#include "../../include/actors/explosion_big_fx.h"
#include "explosion_big_fx.h"

namespace adonai
{
    Explosion_Big_FX::Explosion_Big_FX() :
        _sprite(bn::sprite_items::explosion_big.create_sprite( 120+16, 80+16, 0))
    {
        _sprite.set_z_order(-1);
        _explosion_anim = bn::create_sprite_animate_action_once(
            _sprite,
            10,
            bn::sprite_items::explosion_big.tiles_item(),
            0,1,2,3,4,5
        );
        _sprite.set_visible(false);
    }
    
    void Explosion_Big_FX::init_explosion(const bn::fixed_point pos) {
        if(is_exploding == false){
            is_exploding = true;
            _sprite.set_position(pos);
            _sprite.set_visible(true);
            available = false;
            bn::sound_items::explode_big.play();
        }
    }
    void Explosion_Big_FX::update() 
    {   
        if(available == true) return;

        _explosion_anim.update();
        _sprite.set_position(bn::fixed_point(_sprite.position().x(), _sprite.position().y()-0.15));
        
        if(_explosion_anim.done()){
            _explosion_anim = bn::create_sprite_animate_action_once(
                _sprite, 5, bn::sprite_items::explosion_big.tiles_item(),
                0,1,2,3,4,5
            );
            _sprite.set_visible(false);
            is_exploding = false;
            available = true;
        }
    }
}