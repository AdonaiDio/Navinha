#pragma once

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "shot_player.h"
#include "explosion_fx.h"
#include "enemy.h"

#include "bn_sprite_items_nova.h"
#include "bn_sprite_items_propulsion.h"

#include "bn_log.h"

namespace adonai
{
    extern bn::vector<Enemy*, 20> ntt_enemies;

    enum Player_States{
        Player_NONE = 0,
        //Player_START_MOVE_RIGHT = 1,
        Player_HOLD_MOVE_RIGHT = 2,
        //Player_START_MOVE_LEFT = 3,
        Player_HOLD_MOVE_LEFT = 4
        //idleShoot = IDLE | SHOOTING
    };
    // inline Player_States operator~ (Player_States a) { return (Player_States)~(int)a; }
    // inline Player_States operator| (Player_States a, Player_States b) { return (Player_States)((int)a | (int)b); }
    // inline Player_States operator& (Player_States a, Player_States b) { return (Player_States)((int)a & (int)b); }
    // inline Player_States operator^ (Player_States a, Player_States b) { return (Player_States)((int)a ^ (int)b); }
    // inline Player_States& operator|= (Player_States& a, Player_States b) { return (Player_States&)((int&)a |= (int)b); }
    // inline Player_States& operator&= (Player_States& a, Player_States b) { return (Player_States&)((int&)a &= (int)b); }
    // inline Player_States& operator^= (Player_States& a, Player_States b) { return (Player_States&)((int&)a ^= (int)b); }

        
    class Player
    {
        private:
            bn::sprite_ptr _sprite;
            bn::sprite_ptr _sprite_clone;//Usado no <feedback> de hit
            bn::fixed_point _pos;
            bn::rect _col = bn::rect( 0, 0, 0, 0 );
            bn::sprite_ptr _propulsion_sprite;

            int _hp = 4;
            bn::fixed _speed = 2;

            int hit_feedback_duration = 0;
            int shadow_delay=0;
            bool is_collapsing_shadow = false;
            bn::fixed intensity = 1;
            Explosion_FX* explosion; 

        public:
            // TODO: futuramente com mais tiros, pode ser que passar sprite não seja a melhor solução. 
            // Organizar uma lista de tiros em forma de Enum pode ser o melhor caminho.
            Player(
                bn::sprite_item sprite_item, 
                bn::fixed x, bn::fixed y, 
                bn::sprite_item shot_sprite_item);
            
            bn::array<bn::sprite_ptr, 3> shadow_sprites;
            bn::sprite_ptr sprite() { return _sprite; }
            bn::sprite_ptr propulsion_sprite() { return _propulsion_sprite; }
            
            bool wait_to_destroy = false;
            bool can_act = false;
            bn::fixed moved_to_left = 0;
            
            bn::array<adonai::Shot_Player, 12> _shots;
            Player_States _movement_states = Player_States::Player_NONE;

            bn::sprite_animate_action<3> propulsion_hold_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _propulsion_sprite,
                    0,
                    bn::sprite_items::propulsion.tiles_item(),
                    8,8,8
                );
        
            int hp() { return _hp; }
            void hp(int new_value) { _hp = new_value; }
            bn::fixed speed(){return _speed;};
            
            void hit_feedback();
            void receive_hit();
            void explode();

            bn::fixed_point pos() { return _pos; }
            void pos(bn::fixed_point position) { _pos = position; }
            bn::rect col() { return _col; }

            void set_shot_sprite(bn::sprite_ptr shot_sprite); 

            void check_sprites_states();

            void handle_shadows_rgb();

            void update();
            void test_collision();
            void update_collider();
    };

}