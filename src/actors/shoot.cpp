#include "bn_sprite_actions.h"
#include "bn_display.h"
#include "bn_log.h"
#include "bn_sprite_item.h"

#include "enemy.h"

#include "shoot.h"

namespace adonai
{
    Shoot::Shoot(   const bn::sprite_item& sprite_item, 
                    const bn::fixed_point& initial_position, 
                    const Direction& direction,
                    const Tag& owner_tag)
        :
        _sprite(sprite_item.create_sprite(bn::fixed_point(bn::display::width()+8,0))),
        _pos(initial_position),
        _dir(direction),
        _owner_tag(owner_tag)
    {
        _state = Shoot_State::NONE;
        _sprite.set_visible(false);
    }

    Shoot::~Shoot() {;}

    bn::fixed_point Shoot::pos()
    {
        return _pos;
    }

    void Shoot::set_pos(bn::fixed_point position)
    {
        _pos = position;
    }

    Direction Shoot::dir()
    {
        return _dir;
    }

    bn::sprite_ptr Shoot::sprite()
    {
        return _sprite;
    }

    bn::rect Shoot::col()
    {
        return _col;
    }

    Tag Shoot::owner_tag()
    {
        return _owner_tag;
    }

    void Shoot::set_sprite(bn::sprite_ptr sprite)
    {
        _sprite = sprite;
    }

    const int Shoot::direction_axis_x()
    {
        int axis_x = 1;
        if(_dir == Direction::Right)
        {
            axis_x = 1;
        }
        else if(_dir == Direction::Left)
        {
            axis_x = -1;
        }
        return axis_x;
    }

    // o valor do owner_pos_y deve ser criado ao disparar o tiro
    void Shoot::Move_Forward()
    {
        //não mover se colidir
        if(check_collision()){
            //se colidir resetar estado do tiro
            _pos.set_x((bn::display::width()/2)+4);
            _sprite.set_position(pos());
            _state = Shoot_State::NONE;
            return;
        }
        const int velocity = 2;
        //incrementa a posição em X do shoot
        set_pos(pos() + bn::fixed_point( bn::fixed(direction_axis_x() * velocity), 0) );
        //corrigir a posição do sprite em relação a posição 'pos' dele
        _sprite.set_position(pos());

        // ao chegar no fim da tela volta a ser NONE
        if(_sprite.position().x() > (bn::display::width()/2)+4)
        {
            _state = Shoot_State::NONE;
        }
        //ATUALIZAR COLLISION
        _col = bn::rect( (int)_pos.x(), (int)_pos.y(),
                        4, 1 );
    }

    bool Shoot::check_collision()
    {
        //FIXME: considerar se é bom fazer o check todo frame ou pulando frames
        frame_counter++;
        if(frame_counter < frame_frequency){ return false;}
        frame_counter = 0;
        //BN_LOG("CHECK COLLISION");
        for (int i = 0; i < ntt_enemies.size(); i++)
        {
            //BN_LOG("enemies: ", ntt_enemies.size());
            if ( _col.intersects(ntt_enemies.at(i)->col()))
            {
                BN_LOG("Colidiu!");
                ntt_enemies.at(i)->receive_hit(i);
                return true;
                break;
            }            
        }
        return false;
    }
}
