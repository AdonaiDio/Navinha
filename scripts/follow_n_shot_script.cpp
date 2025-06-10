#pragma once
//butano
#include "bn_log.h"
//assets
//#include <bn_sprite_items_.h>
//my code
#include "../include/utility.h"
#include "enemy.h"
#include "player.h"
//this interface
#include "i_script.hpp"

namespace adonai {
    namespace GLOBALS
    {
        extern Player* global_player;
    }
    class Follow_N_Shot_Script : public I_Script<Enemy>{
        private:
        bn::fixed min_x = 2*16;
        bn::fixed max_x = 4*16;
        // true = min; false = max;
        bool min_max_toggle = true;
        // true = move; false = shoot;
        bool move_shoot_toggle = true;
        
        int next_shoot_timer = 0;
        int count_shots = 0;
        
        public:
        void start(Enemy* e) override
        {
            move_shoot_toggle = true;
            min_max_toggle = true;
        };
        
        void update(Enemy* e) override
        {
            if(GLOBALS::global_player->hp() > 0 && e->hp()>0){
                if(move_shoot_toggle){
                    Move_to_x_range(e);
                }
                else{
                    Shoot(e);
                }
            }
        };

        constexpr bn::fixed y_play_dir(Enemy* e){
            if(e->pos().y() < GLOBALS::global_player->pos().y()){
                return 1;
            }
            else if(e->pos().y() > GLOBALS::global_player->pos().y()){
                return -1;
            }
            return 0;
        };
        void Move_to_x_range(Enemy* e){
            if (min_max_toggle) {
                if (e->pos().x() > min_x) {//vai para esquerda
                    e->pos(move_towards(e->pos(), e->pos()+bn::fixed_point(-1, y_play_dir(e)), e->velocity()));
                }
                else{
                    //chegou? agora atira.
                    move_shoot_toggle = false;
                }
            }
            else{
                if (e->pos().x() < max_x) {//vai para direita
                    e->pos(move_towards(e->pos(), e->pos()+bn::fixed_point(1, y_play_dir(e)), e->velocity()));
                }
                else{
                    //chegou? agora atira.
                    move_shoot_toggle = false;
                }
            }
        }
        void Shoot(Enemy* e){
            next_shoot_timer--;
            if(count_shots < 3 && next_shoot_timer <= 0){
                next_shoot_timer = 30;
                e->shoot();
                count_shots++;
            }else if(count_shots >= 3){
                count_shots = 0;
                min_max_toggle = !min_max_toggle;
                move_shoot_toggle = true;
            }
        }
    };
}