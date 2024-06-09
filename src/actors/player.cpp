#include "player.h"

#include "bn_keypad.h"
#include "bn_sprite_actions.h"

namespace adonai
{
    Player::Player(bn::sprite_ptr sprite) : 
        _sprite(sprite) {}

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

    //FIXME: o player não deveria tratar movimento em um metodo de update de sprite. 
    void Player::update_sprite_position(adonai::Player &player)
    {
        bn::sprite_move_to_action nave_action_moveTo( player.sprite(), 1, player.pos() );
        nave_action_moveTo.update();
    }
}