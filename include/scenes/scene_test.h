#pragma once
//butano
#include <bn_core.h>
#include "bn_log.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_display.h"
#include "bn_colors.h"
#include "bn_bg_palette_color_hbe_ptr.h"
#include "bn_unique_ptr.h"

//my code
#include "scene.h"
#include "i_scene.h"
#include "player.h"
#include "enemy.h"
#include "controller.h"
#include "shot.h"
#include "../../include/hud/hud_energy_bar.h"
#include "../../include/hud/hud_hp_bar.h"
#include "hud_game_over.h"
#include "enemies.cpp"
#include "../../scripts/boss_spawn_enemy_1a.cpp"

//assets
#include "bn_sprite_items_spaceship_1.h"

namespace adonai 
{
    namespace GLOBALS {
        extern Player* global_player;
    }
    class Test : I_Scene
    {       
        private:
            const int grid_width = bn::sprite_items::spaceship_1.shape_size().width();
            const int grid_height = bn::sprite_items::spaceship_1.shape_size().height();
        public:
            Test();
            void SpawnEnemy();
            Scene execute(bn::fixed_point start_pos = {0,0});
            
            bn::vector<Enemy, MAX_ENEMIES> ntt_enemies = bn::vector<Enemy, MAX_ENEMIES>();
            // bn::array<New_Shot_Enemy*, 40> ntt_shots;
            bn::array<Shot_Enemy, 40> ntt_shots = { 
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),
            Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot),Shot_Enemy(bn::sprite_items::shoot)};
        
            DataBase_Enemies db_e;
            Boss_Spawn_Enemy_1A_Script BSE_1a = Boss_Spawn_Enemy_1A_Script();

            // update todos os inimigos na cena
            void update_all_enemies(){
                if(ntt_enemies.size() > 0){
                    for (int i = 0; i < ntt_enemies.size(); i++) {
                        if(ntt_enemies.at(i)._available == false){
                            ntt_enemies.at(i).update();
                        }
                    }
                }
            }
            // update todos os tiros na cena
            void update_all_shoots(){
                for (int i = 0; i < ntt_shots.size(); i++) {
                    if(ntt_shots.at(i)._available == false){
                        ntt_shots.at(i).update();
                    }
                }
            }

            void add_enemy_ntt(Enemy enemy){
                if(ntt_enemies.size() == 0){
                    ntt_enemies.push_back(enemy);
                    return;
                }
                for (int i = 0; i < ntt_enemies.size(); i++) {
                    if(ntt_enemies.at(i)._available == true){
                        ntt_enemies.at(i)._available = false;
                        ntt_enemies.at(i).copy_Enemy( enemy );
                        BN_LOG("using ",ntt_enemies.size()," enemies in list");
                        return;
                    }
                }
                BN_LOG("Não há ntt_enemies nos slots disponíveis.");
                if(ntt_enemies.size() < MAX_ENEMIES){
                    ntt_enemies.push_back(enemy);
                }
                else{
                    BN_LOG("Não há slots em ntt_enemies list.");
                }
            }
    };
};
