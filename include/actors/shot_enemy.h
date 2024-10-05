#pragma once

#include "shot.h"

namespace adonai
{
    class Player; 
    namespace GLOBALS
    {
        extern Player* global_player;
    }

    class Shot_Enemy : public Shot
    {
    private:
        bn::fixed_point _pos;
        bn::sprite_ptr _sprite;
        bn::rect _col;
        const int velocity = 1;
        bn::sprite_item _sprite_item;
    public:
        Shot_Enemy( const bn::sprite_item& sprite_item, 
                    const bn::fixed_point& initial_position = {0,0});
        ~Shot_Enemy();
        
        Shot_State _state;
        //Direção pré-definida para casos de tiros com movimento especial.
        bn::fixed_point pre_direction = {0,0};

        bn::fixed_point pos() override{ return _pos; }
        void pos(bn::fixed_point position) override{ _pos = position; }
        bn::sprite_ptr sprite() override{ return _sprite; }
        void sprite(bn::sprite_ptr sprite) override{ _sprite = sprite; }
        bn::rect col() override{ return _col; }
        bn::sprite_item sprite_item();

        void move_forward() override;
        void move_forward(bn::fixed_point point_direction) override;
        bool check_collision() override;

        void update();
    };
}
