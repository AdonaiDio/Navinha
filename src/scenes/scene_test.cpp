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
#include "player.h"
#include "enemy.h"
#include "controller.h"
#include "shot.h"
#include "../../include/hud/hud_energy_bar.h"
#include "../../include/hud/hud_hp_bar.h"
#include "hud_game_over.h"
#include "enemies.cpp"

#include "inimigo.h"

//assets
#include "bn_sprite_items_gizmos_16x16.h"
#include "bn_regular_bg_items_tela.h"
#include "bn_sprite_items_shoot.h"
#include "bn_sprite_items_spaceship_1.h"
#include "bn_music_items.h"

#include "obj.h"

namespace adonai
{
    namespace GLOBALS {
        extern Player* global_player;
    }


    class Test {       
        private:
        const int grid_width = bn::sprite_items::spaceship_1.shape_size().width();
        const int grid_height = bn::sprite_items::spaceship_1.shape_size().height();

        public:
        bn::vector<Enemy*, 20> ntt_enemies = bn::vector<Enemy*,20>();
        // bn::array<New_Shot_Enemy*, 40> ntt_shots;
        bn::vector<Shot_Enemy*, 40> ntt_shots;

        DataBase_Enemies db_e;
        Test(){
        };

        Scene execute(bn::fixed_point spawn_location)
        {
            adonai::GLOBALS::global_player->ntt_enemies = &ntt_enemies;
            adonai::GLOBALS::global_player->pass_ntt_enemies_to_shots();

            bn::regular_bg_ptr r_bg_1 = bn::regular_bg_items::tela.create_bg(0, 0);
            
            adonai::hud_energy_bar hud_energy_bar = adonai::hud_energy_bar(*adonai::GLOBALS::global_player);
            for (int i = 0; i < hud_energy_bar.energy_bar_sprites.size(); i++)
            {   hud_energy_bar.energy_bar_sprites.at(i).set_z_order(-2); }

            adonai::hud_hp_bar hud_hp_bar = adonai::hud_hp_bar(*adonai::GLOBALS::global_player);
            for (int i = 0; i < hud_hp_bar.hp_bar_sprites.size(); i++)
            {   hud_hp_bar.hp_bar_sprites.at(i).set_z_order(-2); }
            
            adonai::hud_game_over game_over = adonai::hud_game_over(0, -80-16);
            
            BN_LOG("CENA DE TESTE");

            adonai::GLOBALS::global_player->pos(spawn_location);
            adonai::GLOBALS::global_player->sprite().set_visible(true);
            adonai::GLOBALS::global_player->sprite().set_z_order(-1);
            adonai::GLOBALS::global_player->can_act = true;
            // instancia o controller
            adonai::Controller controller = adonai::Controller(*adonai::GLOBALS::global_player);

            BN_LOG("CENA Usados: ", bn::sprites::used_items_count());
            BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
            BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            //inimigos
            Enemy* enemy_1 = new Enemy( &ntt_enemies, 
                                        bn::fixed_point(grid_width*(4),(grid_height*(0))),
                                        bn::sprite_items::spaceship_1,
                                        3,
                                        bn::sprite_items::shoot,
                                        E_Shot_Type::E_Shot_Type_1);
            enemy_1->assign_ntt_shots(&ntt_shots);
            enemy_1->col(bn::rect((int)enemy_1->pos().x()+0, (int)enemy_1->pos().y()+1, 16, 10));
            // Enemy* e_1 = db_e.DefaultEnemy(  bn::fixed_point(grid_width*(4),(grid_height*(0))), &ntt_enemies );
            // Enemy* e_2 = db_e.DefaultEnemy(  bn::fixed_point(grid_width*(4),(grid_height*(0))), &ntt_enemies );
            // Enemy* e_3 = db_e.DefaultEnemy(  bn::fixed_point(grid_width*(4),(grid_height*(0))), &ntt_enemies );
            // Enemy* e_4 = db_e.DefaultEnemy(  bn::fixed_point(grid_width*(4),(grid_height*(0))), &ntt_enemies );
            
            ///
            // BN_LOG("novo sprite de nave por obj");
            // Inimigo* i_1 = db_e.NovoInimigo(  bn::fixed_point(grid_width*(4),(grid_height*(0))), &ntt_enemies  );
            // i_1->assign_ntt_shots(&ntt_shots);
            // Inimigo* i_2 = db_e.NovoInimigo(  bn::fixed_point(grid_width*(4),(grid_height*(1))), &ntt_enemies  );
            // i_2->assign_ntt_shots(&ntt_shots);
            // Inimigo* i_3 = db_e.NovoInimigo(  bn::fixed_point(grid_width*(4),(grid_height*(-1))) );
            // Inimigo* i_4 = db_e.NovoInimigo(  bn::fixed_point(grid_width*(3),(grid_height*(0))) );

            //bn::sprite_ptr sp = bn::sprite_items::spaceship_3.create_sprite({0,0});
            // Obj* o = db_e.NovoObj();
            // Obj* o2 = db_e.NovoObj();
            BN_LOG("inimigos Usados: ", bn::sprites::used_items_count());
            BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
            BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            
            bn::music_items::nova_theme.play();

            while(true)
            {
                controller.update();
                
                // gizmos.set_position(_player->pos());

                // if(enemy_1->hp() > 0 || enemy_1->wait_to_destroy) { enemy_1->update(); }
                
                if(adonai::GLOBALS::global_player->hp() > 0 || adonai::GLOBALS::global_player->wait_to_destroy) { adonai::GLOBALS::global_player->update(); }
                hud_energy_bar.update();
                hud_hp_bar.update();

                update_all_enemies();
                update_all_shots();

                
                if(adonai::GLOBALS::global_player->hp() <= 0){ game_over.update(); }

                
                if (bn::keypad::l_pressed())
                {
                    BN_LOG("Usados: ", bn::sprites::used_items_count());
                    BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
                    BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
                }

                bn::core::update();
            }
        }
        // update todos os inimigos na cena
        void update_all_enemies(){
            if(ntt_enemies.size() > 0){
                for (int i = 0; i < ntt_enemies.size(); i++) {
                    ntt_enemies.at(i)->update();
                }
            }
        }
        void update_all_shots(){
            if(ntt_shots.size() > 0){
                for (int i = 0; i < ntt_shots.size(); i++) {
                    ntt_shots.at(i)->update();
                }
            }
        }

    };
    
}