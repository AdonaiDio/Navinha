#include "bn_log.h"
#include "bn_sound_items.h"

#include "../../include/actors/explosion_fx.h"

namespace adonai
{
    Explosion_FX::Explosion_FX(bn::fixed_point& pos) :
    _sprite(bn::sprite_items::explosion.create_sprite(pos.x(),pos.y(),0)),
    _pos(pos)
    {
        _sprite.set_z_order(-1);
        _explosion_anim = bn::create_sprite_animate_action_once(
            _sprite,
            5,
            bn::sprite_items::explosion.tiles_item(),
            0,1,2,3,4
        );
        bn::sound_items::explode.play();
    }
    Explosion_FX::~Explosion_FX()
    {
        BN_LOG("Terminou");
    }
    
    bn::sprite_ptr Explosion_FX::sprite()
    {
        return _sprite;
    }

    void Explosion_FX::update()
    {
        _explosion_anim.update();
        if(_explosion_anim.done()){
            Explosion_FX::~Explosion_FX();
        }
    }
}