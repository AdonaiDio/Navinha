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

#define MAX_ENEMIES 12
#define MAX_PLAYER_SHOTS 12

namespace adonai
{
    // extern bn::vector<Enemy*, 20> ntt_enemies;
    

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

        
    class Player : public Actor<Player>
    {
        using Actor::Actor;
        private:
            // bn::sprite_ptr _sprite_clone;
            bn::sprite_ptr _propulsion_sprite;

            // int hit_feedback_duration = 0;

            int shadow_delay = 0;
            bool is_collapsing_shadow = false;

        public:
            bn::vector<Enemy, MAX_ENEMIES>* ntt_enemies;//referencia da lista de ntts
            // TODO: futuramente com mais tiros, pode ser que passar sprite não seja a melhor solução. 
            // Organizar uma lista de tiros em forma de Enum pode ser o melhor caminho.
            Player( bn::sprite_item sprite_item,
                    bn::fixed_point position, 
                    bn::sprite_item shot_sprite_item, 
                    int max_hp = 4);
            
            bn::array<bn::sprite_ptr, 3> shadow_sprites;
            bn::sprite_ptr propulsion_sprite() { return _propulsion_sprite; }

            bool can_act = false;
            bn::fixed moved_to_left = 0;
            int shotButton_held_time = 0;
            
            bn::array<adonai::Shot_Player, MAX_PLAYER_SHOTS> _shots;
            // //true se shot tiver disponível
            // bn::array<bool*, 12> _shots_is_available;

            Player_States _movement_states = Player_States::Player_NONE;

            bn::sprite_animate_action<3> propulsion_hold_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _propulsion_sprite,
                    0,
                    bn::sprite_items::propulsion.tiles_item(),
                    8,8,8
                );
        
            
            void hit_feedback();
            void receive_hit(int damage = 1);
            void explode();

            void handle_shadows_rgb();

            void update();
            void pass_ntt_enemies_to_shots();
            
            // void update_all_shots_occupied(){
            //     for (int i = 0; i < _shots_is_available.size(); i++) {
            //         if( *_shots_is_available.at(i) == false){
            //             _shots.at(i).move_forward();
            //         }
            //     }
            // };
            // bool all_shots_available()
            // {
            //     for (int i = 0; i < _shots_is_available.size(); i++)
            //     {
            //         if(*_shots_is_available[i] == false){
            //             return false;
            //         }
            //     }
            //     return true;
            // }
            // int shots_occupied_qty()
            // {
            //     int counter = 0;
            //     for (int i = 0; i < _shots_is_available.size(); i++)
            //     {
            //         if(*_shots_is_available[i] == false){
            //             counter++;
            //         }
            //     }
            //     return counter;
            // }
            
            void update_scripts()
            {
                for (u_int8_t i = 0; i < _scripts.size(); i++)
                {
                    if(_scripts[i] == nullptr){continue;}
                    _scripts[i]->update(this);
                }
            }
            void update_collider();
    };

}