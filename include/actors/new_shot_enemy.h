#pragma once

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_rect.h"
#include "bn_vector.h"
#include "bn_display.h"
#include "bn_sprite_actions.h"
#include "bn_log.h"
#include "bn_sprite_item.h"

#include "utility.h"

#include "e_direction.h"

// #include "shot.h"

namespace adonai
{
    class Player; 
    namespace GLOBALS
    {
        extern Player* global_player;
    }

    class New_Shot_Enemy
    {
    private:
        bn::fixed_point _pos = {0,0};
        bn::sprite_ptr _sprite;
        bn::sprite_item _sprite_item;
        bn::rect _col;
        const int velocity = 1;

    public:
        New_Shot_Enemy(const bn::sprite_item& sprite_item);
        //cria uma copia de outro shot
        New_Shot_Enemy(const New_Shot_Enemy& shot, const bn::fixed_point& initial_position = {0,0});
        ~New_Shot_Enemy();
        
        bn::vector<New_Shot_Enemy*, 40>* ntt_shots;

        bool _available = true;//um substituto ao state NONE e SHOOTING
        //Direção pré-definida para casos de tiros com movimento especial.
        bn::fixed_point pre_direction = {0,0};

        bn::fixed_point pos() { return _pos; } //override do shot
        void pos(bn::fixed_point position) { _pos = position; }//override do shot
        bn::sprite_ptr sprite() { return _sprite; }//override do shot
        void sprite(bn::sprite_ptr sprite) { _sprite = sprite; }//override do shot
        bn::rect col() { return _col; }//override do shot
        // bn::sprite_item sprite_item() { return _sprite_item; }
        // void sprite_item(bn::sprite_item sprite_item) { _sprite_item = sprite_item; }

        void move_forward(); // override do shot
        bool is_out_of_screen(); 
        void move_forward(bn::fixed_point point_direction) ;//override do shot
        bool check_collision() ;//override do shot

        void update();
    };
}
