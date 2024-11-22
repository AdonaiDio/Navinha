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

    class Stage_1
    {       
        private:

        const int grid_width = bn::sprite_items::spaceship_1.shape_size().width();
        const int grid_height = bn::sprite_items::spaceship_1.shape_size().height();

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
        bn::vector<Enemy*, 20> ntt_enemies = bn::vector<Enemy*,20>();
        
        bn::vector<Shot_Enemy*, 40> ntt_shots;
    
        DataBase_Enemies db_e;
        // esse scripts estão na heap!!!
        Move_And_Destroy_Script wave1_move_n_destroy_script;
        // devem ser deletados depois de usado;
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
            start_Wave_3();
            _state = Stage_State::Stage_State_WAVE_3;
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
                    //update_Wave_2();
                    break;
                
                case Stage_State::Stage_State_WAVE_3:
                    if(finished_Wave_3()){
                        //_state = Stage_State::Stage_State_WAVE_4;
                        //start_Wave_4();
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
                if(_state == Stage_State::Stage_State_WAVE_1 && finished_Wave_1()){
                    start_Wave_2();
                    _state = Stage_State::Stage_State_WAVE_2;
                };

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

        // Adiciona enemy a ntt_enemies. 
        // ... na verdade não adiciona, altera um enemy dispoível da lista de ntt_enemies.
        void add_enemy_ntt(Enemy enemy){
            ;
        }

        // update todos os inimigos na cena
        void update_all_enemies(){
            if(ntt_enemies.size() > 0){
                for (int i = 0; i < ntt_enemies.size(); i++) {
                    ntt_enemies.at(i)->update();
                }
            }
        }
        // update todos os tiros na cena
        void update_all_shoots(){
            if(ntt_shots.size() > 0){
                for (int i = 0; i < ntt_shots.size(); i++) {
                    ntt_shots.at(i)->update();
                }
            }
        }
        void start_Wave_1(){
            
            //instancias de inimigos
            Enemy* enemy1 = db_e.DefaultEnemy(  bn::fixed_point(grid_width*(0+8),(grid_height*(0))), &ntt_enemies);
            enemy1->add_script(wave1_move_n_destroy_script);
            // inimigos na diagonal
            // ------//;
            // -----//;
            // ----<;
            // -----\\;
            // ------\\;
            for (int i = 1; i <= 4; i++) 
            {
                Enemy* enemy2 = db_e.DefaultEnemy(  bn::fixed_point(grid_width*(i+8),(grid_height*(i))), &ntt_enemies);
                enemy2->add_script(wave1_move_n_destroy_script);
                Enemy* enemy3 = db_e.DefaultEnemy(  bn::fixed_point(grid_width*(i+8),(grid_height*(-1*i))), &ntt_enemies);
                enemy3->add_script(wave1_move_n_destroy_script);
            }
        }

        //Condição para concluir a primeira wave
        //não ter mais inimigos em tela
        bool finished_Wave_1(){
            if (ntt_enemies.size()<=0) {   return true; }
            return false;
        }

        void start_Wave_2() {
            //vai e volta em zig zag em loop
            //instancias de inimigos
            Enemy* enemy1 = db_e.DefaultEnemy(  bn::fixed_point( 16*(8), (grid_height*(-6)) ), &ntt_enemies );
            enemy1->add_script(wave2_medvd_script_1);
            Enemy* enemy2 = db_e.DefaultEnemy(  bn::fixed_point( 16*(8+1), (grid_height*(-6-1)) ), &ntt_enemies );
            enemy2->add_script(wave2_medvd_script_2);
            Enemy* enemy3 = db_e.DefaultEnemy(  bn::fixed_point( 16*(8+2), (grid_height*(-6-2)) ), &ntt_enemies );
            enemy3->add_script(wave2_medvd_script_3);

            Enemy* enemy4 = db_e.DefaultEnemy(  bn::fixed_point( 16*(8), (grid_height*(6)) ), &ntt_enemies );
            enemy4->add_script(wave2_medvd_script_4);
            Enemy* enemy5 = db_e.DefaultEnemy(  bn::fixed_point( 16*(8+1), (grid_height*(6+1)) ), &ntt_enemies );
            enemy5->add_script(wave2_medvd_script_5);
            Enemy* enemy6 = db_e.DefaultEnemy(  bn::fixed_point( 16*(8+2), (grid_height*(6+2)) ), &ntt_enemies );
            enemy6->add_script(wave2_medvd_script_6);

        }

        bool finished_Wave_2(){
            if (ntt_enemies.size()<=0) {   return true; }
            return false;
        }
        void start_Wave_3() {
            BN_LOG("WAVE 3");
            Enemy* red = db_e.RedEnemy({6*16, (-6*16)}, &ntt_enemies, &ntt_shots);
            red->add_script(wave3_shot_n_run_loop_script_1);
            Enemy* red2 = db_e.RedEnemy({7*16, (-8*16)}, &ntt_enemies, &ntt_shots);
            red2->add_script(wave3_shot_n_run_loop_script_2);
            Enemy* red3 = db_e.RedEnemy({8*16, (-10*16)}, &ntt_enemies, &ntt_shots);
            red3->add_script(wave3_shot_n_run_loop_script_3);
        }
        bool finished_Wave_3(){
            if (ntt_enemies.size()<=0) {   return true; }
            return false;
        }
        void start_Wave_4() {
            BN_LOG("WAVE 4");
            Enemy* pyr = db_e.PyramidEnemy({6*16, (0*16)}, &ntt_enemies);
            pyr->add_script(wave4_f_n_s_script);
        }
        bool finished_Wave_4(){
            if (ntt_enemies.size()<=0) {   return true; }
            return false;
        }
        bool stage_1_is_clear(){

            return false;
        }
        void quit_stage(){

        }
        
    };
}