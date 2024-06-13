#include "bn_sprite_actions.h"
#include "bn_display.h"
#include "bn_log.h"
#include "bn_sprite_item.h"


#include "shoot.h"

namespace adonai
{
    Shoot::Shoot(bn::sprite_item sprite_item, bn::fixed_point initial_position, adonai::Direction direction)
        :
        _sprite(sprite_item.create_sprite(bn::fixed_point(0,0))),
        _pos(initial_position),
        _dir(direction)
    {
        this->_state = adonai::Shoot_State::NONE;
        //this->_sprite.set_visible(false);
    }

    Shoot::~Shoot() {}

    bn::fixed_point Shoot::pos()
    {
        return _pos;
    }

    void Shoot::set_pos(bn::fixed_point position)
    {
        this->_pos = position;
    }

    adonai::Direction Shoot::dir()
    {
        return _dir;
    }

    bn::sprite_ptr Shoot::sprite()
    {
        return _sprite;
    }

    void Shoot::set_sprite(bn::sprite_ptr sprite)
    {
        this->_sprite = sprite;
    }

    const int Shoot::direction_axis_x()
    {
        int axis_x = 1;
        if(this->_dir == adonai::Direction::Right)
        {
            axis_x = 1;
        }
        else if(this->_dir == adonai::Direction::Left)
        {
            axis_x = -1;
        }
        return axis_x;
    }

    // o valor do owner_pos_y deve ser criado ao disparar o tiro
    void Shoot::Move_Forward()
    {
        //bn::sprite_move_to_action move_forward_action(_sprite, 60, bn::fixed_point(direction_axis_x() * (bn::display::width()/2)+8, _pos.y()));
        //move_forward_action.update();
        const int velocity = 2;
        //incrementa a posição em X do shoot
        this->set_pos(pos() + bn::fixed_point( bn::fixed(direction_axis_x() * velocity), 0) );
        //corrigir a posição do sprite em relação a posição 'pos' dele
        this->_sprite.set_position(pos());

        // ao chegar no fim da tela volta a ser NONE
        if(this->_sprite.position().x() > (bn::display::width()/2)+4)
        {
            this->_state = adonai::Shoot_State::NONE;
        }
        BN_LOG("instancia shoot em: x:", this->_pos.x(), " y:", this->_pos.y());
        BN_LOG("instancia shoot sprite em: x:", this->_sprite.position().x(), " y:", this->_sprite.position().y());
    }

}
