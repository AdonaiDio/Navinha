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
            bn::rect _col;
        bn::sprite_item _sprite_item;
    public:
        Shot_Enemy(const bn::sprite_item& sprite_item);
        //cria uma copia de outro shot_enemy
        Shot_Enemy(const Shot_Enemy& shot, const bn::fixed_point& initial_position = {0,0});
        ~Shot_Enemy();
        
        bn::vector<Shot_Enemy*, 40>* ntt_shots;

        // bool _available = true;//um substituto ao state NONE e SHOOTING. Seve para tiro predefinidos não instanciados.
        //Direção pré-definida para casos de tiros com movimento especial.
        bn::fixed_point pre_direction = {0,0};

        bn::fixed_point pos() override{ return _pos; }
        void pos(bn::fixed_point position) override{ _pos = position; }
        bn::sprite_ptr sprite() override{ return _sprite; }
        void sprite(bn::sprite_ptr sprite) override{ _sprite = sprite; }
        bn::rect col() override{ return _col; }
        void col(bn::rect collision) override{ _col = collision; }
        void col_dimension(bn::size dimensions) { _col.set_dimensions(dimensions); } //override?
        void col_position(bn::point position) { _col.set_position(position); } //override?
        // bn::sprite_item sprite_item() { return _sprite_item; }
        // void sprite_item(bn::sprite_item sprite_item) { _sprite_item = sprite_item; }

        void move_forward() override;
        bool is_out_of_screen(); 
        // void move_forward(bn::fixed_point point_direction) override;
        bool check_collision() override;

        void update();
    };
}
