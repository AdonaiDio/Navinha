#include "bn_log.h"
// #include "bn_sound_items.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_colors.h"

#include "hit_fx.h"

namespace adonai
{
    Hit_FX::Hit_FX( bn::fixed_point& pos, bn::sprite_item sprite_item, 
                    int sprite_index, bool& is_hitting) :
    _pos(pos),
    _sprite(sprite_item.create_sprite(pos, sprite_index)),
    _palette(bn::sprite_palette_ptr::create_new(sprite_item.palette_item())), 
    _is_hitting(is_hitting)
    {
        _sprite.set_z_order(-2);
        _sprite.set_palette(_palette);
        _sprite.set_visible(false);
    }
    Hit_FX::Hit_FX( bn::fixed_point& pos, 
                    bn::sprite_item sprite_item, 
                    bool& is_hitting) :
    _pos(pos),
    _sprite(sprite_item.create_sprite(pos)),
    _palette(bn::sprite_palette_ptr::create_new(sprite_item.palette_item())), 
    _is_hitting(is_hitting)
    {
        _sprite.set_z_order(-2);
        _sprite.set_palette(_palette);
        _sprite.set_visible(false);
    }
    Hit_FX::~Hit_FX()
    {
        _is_hitting = false;
    }
    
    bn::sprite_ptr Hit_FX::sprite()
    {
        return _sprite;
    }

    void Hit_FX::update()
    {
        if(!_is_hitting) return;
        if (hit_feedback_duration > 0)
        {
            //bn::sprite_palette_ptr _palette = _sprite.palette();
            //muda as cores para as cores do enemy que está levando hit já que a palette é compartilhada
            for (int i = 0; i < _sprite.palette().colors().size(); i++)
            {
                _palette.set_color(i,_sprite.palette().colors().at(i));
            }
            
            if (hit_feedback_duration % 15 == 0) //se for divisível por 15
            {
                _palette.set_fade(bn::colors::white, intensity);
                intensity = 1;
            }
            else
            {
                intensity = bn::clamp((bn::fixed(-0.1) + intensity), bn::fixed(0), bn::fixed(1));
                _palette.set_fade(bn::colors::white, intensity);
            }
            hit_feedback_duration--;
            if(hit_feedback_duration == 0){
                _is_hitting = false;
            }
        } 
        _sprite.set_position(_pos);

    }
}