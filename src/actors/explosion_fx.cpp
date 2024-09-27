#include "bn_log.h"
#include "bn_sound_items.h"

#include "../../include/actors/explosion_fx.h"

namespace adonai
{
    Explosion_FX::Explosion_FX(bn::fixed_point& pos) :
    _sprite(bn::sprite_items::explosion.create_sprite(pos.x(),pos.y(),0))
    {
        _sprite.set_z_order(-1);
        _explosion_anim = bn::create_sprite_animate_action_once(
            _sprite,
            5,
            bn::sprite_items::explosion.tiles_item(),
            0,1,2,3,4
        );
        bn::sound_items::explode.play();
        BN_LOG("NOVA EXPLO");
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
        BN_LOG("update xplo");
        _explosion_anim.update();
        _sprite.set_position(bn::fixed_point(_sprite.position().x()-1.5, _sprite.position().y()));

        if(_explosion_anim.done()){
            Explosion_FX::~Explosion_FX();
        }
    }
}