#include "player.h"

namespace adonai
{
    Player::Player(bn::sprite_ptr sprite) : 
        _sprite(sprite) {}

    bn::fixed_point Player::pos(){
        return _pos;
    }

    void Player::spawn(bn::fixed_point location)
    {
        _pos = location;
    }
}