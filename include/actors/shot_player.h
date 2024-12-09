#pragma once

#include "shot.h"
#define MAX_ENEMIES 20

namespace adonai
{
    class Shot_Player : public Shot
    {
    private:
        bn::fixed_point _pos;
        bn::sprite_ptr _sprite;
        bn::rect _col = bn::rect( (int)_pos.x(), (int)_pos.y(),
                        4, 2 );
        const int velocity = 3;
    public:
        Shot_Player(    const bn::sprite_item& sprite_item, 
                        const bn::fixed_point& initial_position);
        ~Shot_Player();
        bn::vector<Enemy, MAX_ENEMIES>* ntt_enemies;
        
        Shot_State _state;
        // bool _available = true;
        
        bn::fixed_point pos() override{ return _pos; }
        void pos(bn::fixed_point position) override{ _pos = position; }
        bn::sprite_ptr sprite() override{ return _sprite; }
        void sprite(bn::sprite_ptr sprite) override{ _sprite = sprite; }
        bn::rect col() override{ return _col; }
        void col(bn::rect collision) override{ _col = collision; }

        void move_forward() override;
        // void move_forward(bn::fixed_point point_direction) override;
        bool check_collision() override;
    };
}
