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
    class Shot_N_Run_Loop_Script : public I_Script<Enemy>{
        private:
        int count_frames_update = 0;
        int count_shots = 0;
        
        public:
        void start(Enemy* e) override {
            count_frames_update = 0;
        };
        
        void update(Enemy* e) override {
            if(IsOutOfSight(e->pos().y())){
                e->pos(StartPosition());
                return;
            }
            Move_N_Shoot(e);
        };

        bn::fixed_point StartPosition(){
            count_frames_update = 0;
            count_shots = 0;
            return bn::fixed_point(6*16, -6*16);
        }

        void Move_N_Shoot(Enemy* e){
            e->pos(move_towards(e->pos(), bn::fixed_point(e->pos().x()-1,e->pos().y()+2), e->velocity()));
            Shoot(e);
        }

        bool IsOutOfSight(bn::fixed y){
            if(y >= 6*16){
                return true;
            }
            return false;
        }

        void Shoot(Enemy* e){
            if(GLOBALS::global_player->hp() > 0 && e->hp()>0){
                count_frames_update++;
                if(count_shots > 0){
                    if(count_frames_update >= 30*1){
                        count_shots = 0;
                    }
                    return;
                }
                if (count_frames_update >= 30){
                    count_frames_update = 0;
                    e->shoot();
                    count_shots++;
                }
            }
        }
    };
} 