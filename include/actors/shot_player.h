#pragma once

#include "shot.h"

namespace adonai
{
    class Shot_Player : public Shot
    {
    private:
        bn::fixed_point _pos;
        bn::sprite_ptr _sprite;
        bn::rect _col;
        const int velocity = 3;
    public:
        Shot_Player(    const bn::sprite_item& sprite_item, 
                        const bn::fixed_point& initial_position);
        ~Shot_Player();
        
        Shot_State _state;

        bn::fixed_point pos() override{ return _pos; }
        void pos(bn::fixed_point position) override{ _pos = position; }
        bn::sprite_ptr sprite() override{ return _sprite; }
        void sprite(bn::sprite_ptr sprite) override{ _sprite = sprite; }
        bn::rect col() override{ return _col; }

        void Move_Forward() override;
        bool check_collision() override;
    };
}
