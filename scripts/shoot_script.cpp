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
    

    class Shoot_Script : public I_Script<Enemy>{
        private:
            int count_frames_update = 0;
        public:
            void start(Enemy* enemy) override {
                count_frames_update = 0;
            };
            void update(Enemy* enemy) override {
            // teste de tiro
            // se o player está vivo
            if(GLOBALS::global_player->hp() > 0){
                count_frames_update++;
                if (count_frames_update > 14){
                    count_frames_update = 0;
                    if(enemy->hp()>0)
                    {
                        enemy->shoot();
                        count_frames_update = 0;
                    }
                }
            }

            };
    };
}