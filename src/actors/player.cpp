#include "player.h"

#include "bn_keypad.h"
#include "bn_sprite_actions.h"

namespace adonai
{
    Player::Player(bn::sprite_ptr sprite, bn::sprite_item shoot_sprite_item) : 
        _sprite(sprite)
        ,_shoots({
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right)
        }) 
    {

    }

    bn::sprite_ptr Player::sprite()
    {
        return _sprite;
    }

    bn::fixed_point Player::pos()
    {
        return _pos;
    }
    void Player::set_pos(bn::fixed_point location){
        _pos = location;
    }

    void Player::spawn(bn::fixed_point location)
    {
        //TODO: Relativo ao background
        _pos = location;
    }

    void Player::set_shoot_sprite(bn::sprite_ptr shoot_sprite)
    {
        for(int i=0; i<_shoots.max_size(); i++)
        {
            _shoots[i].set_sprite(shoot_sprite);
        }
    }

    //FIXME: o player não deveria tratar movimento em um metodo de update de sprite. 
    void Player::update_sprite_position(adonai::Player &player)
    {
        bn::sprite_move_to_action nave_action_moveTo( player.sprite(), 1, player.pos() );
        nave_action_moveTo.update();
    }
}