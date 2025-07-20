#pragma once

//butano
#include <bn_core.h>
#include "bn_log.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_display.h"
#include "bn_colors.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"
#include "bn_bg_palette_color_hbe_ptr.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_unique_ptr.h"

#include "bn_keypad.h"

//assets
// #include "bn_sprite_items_gizmos_16x16.h"
#include "bn_regular_bg_items_sky_solid_color.h"
#include "bn_sprite_items_shoot.h"
#include "bn_music_items.h"

//my code
#include <../include/utility.h>
#include "scene.h"
#include "i_scene.h"
#include "player.h"
#include "enemy.h" //
#include "shot_enemy.h"
#include "enemies.cpp"
#include "controller.h"
#include "../../include/effects/bg_fx.h"
#include "../../include/actors/shot_enemy.h"
#include "../../include/hud/hud_energy_bar.h"
#include "../../include/hud/hud_hp_bar.h"
#include "hud_game_over.h"
// #include "ntt_list_stage_1.h"

#include "boss1.h"

//scripts
// #include <D:/Adonai/My_ROMs/Navinha/scripts/i_script.hpp>
//scripts embbeded


#define MAX_ENEMIES 20
#define MAX_SHOTS 40

namespace adonai 
{
    namespace GLOBALS
    {
        extern Player* global_player;
    }
    /*A palavra-chave "inline" diz ao compilador para substituir o código 
    dentro da definição da função para cada instância de uma chamada de função.
    
    Teoricamente era pra funcionar apenas declarando aqui, 
    mas ele causou esse erro, então o inline resolveu o problema.*/

    class Stage_1_Boss : I_Scene
    {       
        private:

        const int grid_width = bn::sprite_items::spaceship_1.shape_size().width();
        const int grid_height = bn::sprite_items::spaceship_1.shape_size().height();

        
        int timer = 0;

        public:
        // bn::vector<Enemy*, 20> ntt_enemies = bn::vector<Enemy*,20>();
        // bn::array<Enemy, MAX_ENEMIES> ntt_enemies = {
        //     Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3),
        //     Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3),
        //     Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3),
        //     Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3),
        //     Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3), Enemy({0,0}, bn::sprite_items::spaceship_1,3)};
        
        bn::vector<Enemy, MAX_ENEMIES> ntt_enemies = bn::vector<Enemy, MAX_ENEMIES>();
        // bn::vector<Explosion_FX, (MAX_ENEMIES/2)> ntt_explosions = bn::vector<Explosion_FX, (MAX_ENEMIES/2)>();
        
        //receberá novas configurações de Shot_enemy nos slots não usados.
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
        
        
        Stage_1_Boss(){ 
        };


        Scene execute(bn::fixed_point spawn_location)
        {
            //associando o player a cena.
            adonai::GLOBALS::global_player->ntt_enemies = &ntt_enemies;
            adonai::GLOBALS::global_player->pass_ntt_enemies_to_shots();
            
            //Start Background
            bn::regular_bg_ptr r_bg_1 = bn::regular_bg_items::sky_solid_color.create_bg(0, 0);

            //Start Scripts
            //Start HUD
            adonai::hud_energy_bar hud_energy_bar = adonai::hud_energy_bar(*adonai::GLOBALS::global_player);
            for (int i = 0; i < hud_energy_bar.energy_bar_sprites.size(); i++)
            {   hud_energy_bar.energy_bar_sprites.at(i).set_z_order(-2); }

            adonai::hud_hp_bar hud_hp_bar = adonai::hud_hp_bar(*adonai::GLOBALS::global_player);
            for (int i = 0; i < hud_hp_bar.hp_bar_sprites.size(); i++)
            {   hud_hp_bar.hp_bar_sprites.at(i).set_z_order(-2); }
            
            adonai::hud_game_over game_over = adonai::hud_game_over(0, -80-16);
            
            BN_LOG("Entrou na cena Stage_1_Boss");

            //Start Entities
            adonai::GLOBALS::global_player->pos(spawn_location);
            adonai::GLOBALS::global_player->sprite().set_visible(true);
            adonai::GLOBALS::global_player->sprite().set_z_order(-1);
            adonai::GLOBALS::global_player->can_act = true;
            // instancia o controller
            adonai::Controller controller = adonai::Controller(*adonai::GLOBALS::global_player);

            //-----START BOSS-----//
            Boss1 boss = Boss1(bn::fixed_point(0,0));
            boss.assign_ntt_shots(&ntt_shots);
            // Add as partes individuais(que se comportam como inimigos)
            add_enemy_ntt(boss.part_shots);
            add_enemy_ntt(boss.part_laser);
            //retornar para o boss os ponteiros dessas partes
            for (int i = 0; i < ntt_enemies.size(); i++)
            {
                if(ntt_enemies[i].sprite() == boss.part_shots.sprite()){
                    boss.part_shots_ptr = &ntt_enemies.at(i);
                }
                if(ntt_enemies[i].sprite() == boss.part_laser.sprite()){
                    boss.part_laser_ptr = &ntt_enemies.at(i);
                }
            }
            //---------------------//

            bn::music_items::nova_theme.play();

            // int count_frames_update = 0;
            
            while(true)
            {
                //---r_bg_1 side scroll---//
                #include  "../../include/effects/bg_fx.hpp"
                BG_GRADIENT_FX(r_bg_1);
                r_bg_1.set_position( bn::fixed_point(r_bg_1.position().x()-((bn::fixed) 0.033f), 0));
                //------------------------//

                if(adonai::GLOBALS::global_player->hp() > 0){
                    update_all_enemies();
                    update_all_shoots();
                    boss.update();
                    
                    controller.update();
                    hud_energy_bar.update();
                    hud_hp_bar.update();
                }

                if(adonai::GLOBALS::global_player->hp() > 0 || adonai::GLOBALS::global_player->wait_to_destroy) { 
                    adonai::GLOBALS::global_player->update(); 
                }
                
                if(adonai::GLOBALS::global_player->hp() <= 0){ 
                    game_over.update(); 
                    if(is_stage_clear()){
                        return quit_stage();
                    }
                }
                if(boss.state == Boss1::BOSS_1_STATES::BOSS_1_DEAD){
                    if(is_stage_clear()){
                        return quit_stage();
                    }
                }

                #pragma region DEBUG
                //---DEBUG KEY---//
                if (bn::keypad::l_pressed())
                {
                    BN_LOG("Usados: ", bn::sprites::used_items_count());
                    BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
                    BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
                    BN_LOG("inimigos: ", ntt_enemies.size());
                    BN_LOG("inimigos dispo.: ", all_available_enemies());
                }
                //---------------//

                //==DEBUG CPU USAGE==//
                // bn::fixed max_cpu_usage = bn::max(max_cpu_usage, bn::core::last_cpu_usage());
                // --counter;
                // if(! counter)
                // {
                //     BN_LOG((max_cpu_usage * 100).right_shift_integer(), "%");
                //     max_cpu_usage = 0;
                //     counter = 10;
                // }
                // ==================//
                #pragma endregion
                
                

                bn::core::update();
            }
        };
        int all_available_enemies(){
            int count = 0;
            for (int i = 0; i < ntt_enemies.size(); i++)
            {
                if (ntt_enemies.at(i)._available)
                {
                    count++;
                }
                
            }
            return count;
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
        
        bool is_stage_clear(){
            BN_LOG("timer:",timer);
            if(timer > 240){
                return true;
            }
            ++timer;

            return false;
        }
        Scene quit_stage(){
            GLOBALS::global_player->sprite().set_visible(false);
            return Scene::CREDITS;
        }
        
    };
}