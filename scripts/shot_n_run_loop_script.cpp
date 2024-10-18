#pragma once
//butano
#include "bn_log.h"
#include "bn_random.h"
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
        int next_shoot_timer = 0;
        bool tri_shooting=false;
        bn::random rand = bn::random();
        
        const bn::array<int,3> rand_frame_num = {-15,0,15};

        public:
        void start(Enemy* e) override {
            count_frames_update = 0;
        };
        
        void update(Enemy* e) override {
            if(IsOutOfSight(e->pos().y()) && e->pos().y() > 0){
                e->pos(StartPosition());
                return;
            }
            Move_N_Shoot(e);
            if(tri_shooting){ // uso uma bool para triggar o tiro para que ele seja processado todo frame
                Triple_Shoot(e);
            }
        };

        bn::fixed_point StartPosition(){
            return bn::fixed_point(6*16, -6*16);
        }

        void Move_N_Shoot(Enemy* e){
            e->pos(move_towards(e->pos(), bn::fixed_point(e->pos().x()-1,e->pos().y()+2), e->velocity()));
            Shoot(e);
        }

        bool IsOutOfSight(bn::fixed y){
            if(y >= 6*16 || y < -5*16){
                return true;
            }
            return false;
        }

        void Shoot(Enemy* e){
            if(GLOBALS::global_player->hp() > 0 && e->hp()>0){
                if(e->pos().y() >= -80 && !IsOutOfSight(e->pos().y())){
                    count_frames_update++;
                    if (count_frames_update >= 55 ){
                        count_frames_update = 0;
                        tri_shooting = true;
                    }
                }
            }
        }
        void Triple_Shoot(Enemy* e){
            next_shoot_timer--;
            if(count_shots < 3 && next_shoot_timer <= 0){
                next_shoot_timer = 15;
                e->shoot();
                count_shots++;
            }else if(count_shots >= 3){
                count_shots = 0;

                tri_shooting = false;
            }
        }
    };
} 