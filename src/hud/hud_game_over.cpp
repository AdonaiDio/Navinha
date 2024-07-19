#include "bn_log.h"

#include "hud_game_over.h"

namespace adonai
{
    hud_game_over::hud_game_over(int x, int y) :
    _pos(x, y),
    _sprites({
        bn::sprite_items::game_over.create_sprite(x-16, y, 0),
        bn::sprite_items::game_over.create_sprite(x, y, 1),
        bn::sprite_items::game_over.create_sprite(x+16, y, 2)
    })
    {
        for (int i = 0; i < _sprites.size(); i++)
        {   
            _sprites.at(i).set_z_order(-2); 
        }
        BN_LOG("gameover iniciado");
    }
    hud_game_over::~hud_game_over() { }

    void hud_game_over::pos(int x, int y)
    {
        _pos = bn::fixed_point(x, y);
    }

    bn::fixed_point hud_game_over::pos()
    {
        return _pos;
    }

    void hud_game_over::update()
    {
        if(_pos.y() < 0){
            BN_LOG(">game over desce");
            _pos = bn::fixed_point(0, _pos.y()+2);

            _sprites.at(0).set_position(_pos.x()-16, _pos.y());
            _sprites.at(1).set_position(_pos.x(), _pos.y());
            _sprites.at(2).set_position(_pos.x()+16, _pos.y());
        }

    }
}