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
#include "enemy.h"
#include "shot_enemy.h"
#include "enemies.cpp"
#include "controller.h"
#include "../../include/effects/bg_fx.h"
#include "../../include/actors/shot_enemy.h"
#include "../../include/hud/hud_energy_bar.h"
#include "../../include/hud/hud_hp_bar.h"
#include "hud_game_over.h"
// #include "ntt_list_stage_1.h"


//scripts
// #include <D:/Adonai/My_ROMs/Navinha/scripts/i_script.hpp>
//scripts embbeded
#include "shoot_script.cpp"
#include "move_and_destroy_script.cpp"
#include "move_enemy_dvd_script.cpp"
#include "shot_n_run_loop_script.cpp"
#include "follow_n_shot_script.cpp"

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

    class Stage_1 : I_Scene
    {       
        private:

        const int grid_width = 16;
        const int grid_height = 16;

        enum Stage_State : int8_t {
            Stage_State_NONE    = 0b00000000,
            Stage_State_START   = 0b00000001,
            Stage_State_WAVE_1  = 0b00000010,
            Stage_State_WAVE_2  = 0b00000100,
            Stage_State_WAVE_3  = 0b00001000,
            Stage_State_WAVE_4  = 0b00010000,
            Stage_State_END     = 0b01111111 //max char u_int8
        };
        Stage_State _state = Stage_State_NONE;
            
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
        Move_And_Destroy_Script wave1_move_n_destroy_script;
        Move_Enemy_DVD_Script wave2_medvd_script_1 = Move_Enemy_DVD_Script();
        Move_Enemy_DVD_Script wave2_medvd_script_2 = Move_Enemy_DVD_Script();
        Move_Enemy_DVD_Script wave2_medvd_script_3 = Move_Enemy_DVD_Script();
        Move_Enemy_DVD_Script wave2_medvd_script_4 = Move_Enemy_DVD_Script();
        Move_Enemy_DVD_Script wave2_medvd_script_5 = Move_Enemy_DVD_Script();
        Move_Enemy_DVD_Script wave2_medvd_script_6 = Move_Enemy_DVD_Script();
        Shot_N_Run_Loop_Script wave3_shot_n_run_loop_script_1 = Shot_N_Run_Loop_Script();
        Shot_N_Run_Loop_Script wave3_shot_n_run_loop_script_2 = Shot_N_Run_Loop_Script();
        Shot_N_Run_Loop_Script wave3_shot_n_run_loop_script_3 = Shot_N_Run_Loop_Script();
        Follow_N_Shot_Script wave4_f_n_s_script = Follow_N_Shot_Script();
        
        Stage_1(){ 

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
            
            BN_LOG("Entrou na cena Stage_1");
            _state = Stage_State::Stage_State_START;
            ////
            //iniciar a primeira horda e contadores
            start_Wave_1();
            _state = Stage_State::Stage_State_WAVE_1;
            // start_Wave_4();
            // _state = Stage_State::Stage_State_WAVE_4;
            ////

            //Start Entities
            adonai::GLOBALS::global_player->pos(spawn_location);
            adonai::GLOBALS::global_player->sprite().set_visible(true);
            adonai::GLOBALS::global_player->sprite().set_z_order(-1);
            adonai::GLOBALS::global_player->can_act = true;
            // instancia o controller
            adonai::Controller controller = adonai::Controller(*adonai::GLOBALS::global_player);

            bn::music_items::nova_theme.play();

            int count_frames_update = 0;
            
            while(true)
            {
                ///////
                //eu não sei... Coloquei isso aí para reutilizar igual em outro lugar. eu acho.
                #include  "../../include/effects/bg_fx.hpp"
                BG_GRADIENT_FX(r_bg_1);
                // r_bg_1 side scroll
                r_bg_1.set_position( bn::fixed_point(r_bg_1.position().x()-((bn::fixed) 0.033f), 0));
                ///////
                
                /////
                switch (_state)
                {
                case Stage_State::Stage_State_WAVE_1:
                    if(finished_Wave_1()){
                        _state = Stage_State::Stage_State_WAVE_2;
                        start_Wave_2();
                    };
                    break;

                case Stage_State::Stage_State_WAVE_2:
                    if(finished_Wave_2()){
                        _state = Stage_State::Stage_State_WAVE_3;
                        start_Wave_3();
                    };
                    break;
                
                case Stage_State::Stage_State_WAVE_3:
                    if(finished_Wave_3()){
                        _state = Stage_State::Stage_State_WAVE_4;
                        start_Wave_4();
                    };
                    break;

                case Stage_State::Stage_State_WAVE_4:
                    if(finished_Wave_4()){
                        _state = Stage_State::Stage_State_END;
                        quit_stage();
                    };
                    break;
                
                default:
                    BN_LOG("Estado da fase não esperado!");
                    break;
                }
                /////

                update_all_enemies();
                update_all_shoots();

                controller.update();

                if(adonai::GLOBALS::global_player->hp() > 0 || adonai::GLOBALS::global_player->wait_to_destroy) { adonai::GLOBALS::global_player->update(); }
                hud_energy_bar.update();
                hud_hp_bar.update();
                
                if(adonai::GLOBALS::global_player->hp() <= 0){ game_over.update(); }


                if (bn::keypad::l_pressed())
                {
                    BN_LOG("Usados: ", bn::sprites::used_items_count());
                    BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
                    BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
                    BN_LOG("inimigos: ", ntt_enemies.size());
                    BN_LOG("inimigos dispo.: ", all_available_enemies());
                }

                
                // //DEBUG CPU USAGE=================
                // bn::fixed max_cpu_usage = bn::max(max_cpu_usage, bn::core::last_cpu_usage());
                // --counter;

                // if(! counter)
                // {
                //     BN_LOG((max_cpu_usage * 100).right_shift_integer(), "%");
                //     max_cpu_usage = 0;
                //     counter = 10;
                // }
                // //=================

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
        void start_Wave_1(){
            BN_LOG("WAVE 1: ", ntt_enemies.size());

            bn::fixed_point position;

            position = {grid_width*(0+8),(grid_height*(0))};
            add_enemy_ntt( db_e.DefaultEnemy(position) );

            for (int i = 1; i <= 4; i++) 
            {
                position = {grid_width*(i+8),(grid_height*(i))};
                add_enemy_ntt( db_e.DefaultEnemy(  position) );
                
                position = {grid_width*(i+8),(grid_height*(-1*i))};
                add_enemy_ntt( db_e.DefaultEnemy(  position) );
            }
            for (int i = 0; i < 9; i++)
            {
                ntt_enemies.at(i).add_script(wave1_move_n_destroy_script);
            }
        }

        //Condição para concluir a primeira wave
        //não ter mais inimigos em tela
        bool finished_Wave_1(){
            for (int i = 0; i < ntt_enemies.size(); i++)
            {
                if (ntt_enemies.at(i)._available ==  false) {
                    return false;
                }
            }
            ntt_enemies.clear();
            BN_LOG("Finish WAVE 1. size: ", ntt_enemies.size());
            return true; 
        }

        void start_Wave_2() {
            BN_LOG("WAVE 2: ", ntt_enemies.size());

            add_enemy_ntt( db_e.DefaultEnemy(  bn::fixed_point( 16*(8), (grid_height*(-6)) ) ) );
            add_enemy_ntt( db_e.DefaultEnemy(  bn::fixed_point( 16*(8+1), (grid_height*(-6-1)) ) ) );
            add_enemy_ntt( db_e.DefaultEnemy(  bn::fixed_point( 16*(8+2), (grid_height*(-6-2)) ) ) );
            add_enemy_ntt( db_e.DefaultEnemy(  bn::fixed_point( 16*(8), (grid_height*(6)) ) ) );
            add_enemy_ntt( db_e.DefaultEnemy(  bn::fixed_point( 16*(8+1), (grid_height*(6+1)) ) ) );
            add_enemy_ntt( db_e.DefaultEnemy(  bn::fixed_point( 16*(8+2), (grid_height*(6+2)) ) ) );

            for (int i = 0; i < ntt_enemies.size(); i++)
            {
                switch (i)
                {
                case 0:
                ntt_enemies.at(i).add_script(wave2_medvd_script_1);
                break;
                case 1:
                ntt_enemies.at(i).add_script(wave2_medvd_script_2);
                break;
                case 2:
                ntt_enemies.at(i).add_script(wave2_medvd_script_3);
                break;
                case 3:
                ntt_enemies.at(i).add_script(wave2_medvd_script_4);
                break;
                case 4:
                ntt_enemies.at(i).add_script(wave2_medvd_script_5);
                break;
                case 5:
                ntt_enemies.at(i).add_script(wave2_medvd_script_6);
                break;
                default:break;
                }
            }
        }

        bool finished_Wave_2(){
            for (int i = 0; i < ntt_enemies.size(); i++)
            {
                if (ntt_enemies.at(i)._available ==  false) {
                    return false;
                }
            }
            ntt_enemies.clear();
            BN_LOG("Finish WAVE 2. size: ", ntt_enemies.size());
            return true; 
        }
        void start_Wave_3() {
            BN_LOG("WAVE 3: ", ntt_enemies.size());
            bn::fixed_point position;
            
            for (int i = 0; i < 3; i++)
            {
                switch (i)
                {
                case 0:
                position = {6*16, (-6*16)};
                break;
                case 1:
                position = {7*16, (-8*16)};
                break;
                case 2:
                position = {8*16, (-10*16)};
                break;
                default:break;
                }
                ntt_enemies.push_back( db_e.RedEnemy(position,  &ntt_shots) );
            }
            for (int i = 0; i < ntt_enemies.size(); i++)
            {
                switch (i)
                {
                case 0:
                ntt_enemies.at(i).add_script(wave3_shot_n_run_loop_script_1);
                break;
                case 1:
                ntt_enemies.at(i).add_script(wave3_shot_n_run_loop_script_2);
                break;
                case 2:
                ntt_enemies.at(i).add_script(wave3_shot_n_run_loop_script_3);
                break;
                default:break;
                }
            }
        }
        bool finished_Wave_3(){
            for (int i = 0; i < ntt_enemies.size(); i++)
            {
                if (ntt_enemies.at(i)._available ==  false) {
                    return false;
                }
            }
            ntt_enemies.clear();
            BN_LOG("Finish WAVE 3. size: ", ntt_enemies.size());
            return true; 
        }
        void start_Wave_4() {
            BN_LOG("WAVE 4");

            ntt_enemies.push_back( db_e.PyramidEnemy({6*16, (0*16)},  &ntt_shots) );
            ntt_enemies.at(0).add_script(wave4_f_n_s_script);
        }
        bool finished_Wave_4(){
            for (int i = 0; i < ntt_enemies.size(); i++)
            {
                if (ntt_enemies.at(i)._available ==  false) {
                    return false;
                }
            }
            ntt_enemies.empty();
            return true; 
        }
        bool stage_1_is_clear(){

            return false;
        }
        void quit_stage(){

        }
        
    };
}