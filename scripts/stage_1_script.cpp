#pragma once
//butano
#include <bn_log.h>
//assets
//#include <bn_sprite_items_.h>
#include "bn_sprite_items_shoot.h"
//my code
#include <../include/utility.h>
#include <../include/scenes/scene_stage_1.h>
#include "enemy.h"
#include "enemies.cpp"
//other script embbeded
#include "move_and_destroy_script.cpp"
#include "move_enemy_dvd_script.cpp"

//this interface
#include <D:/Adonai/My_ROMs/Navinha/scripts/i_script.hpp>

/*
TODO: 

>Spawn diferentes tipos de inimigos

>Inimigos ativos ficam na lista de ntts da cena

>Separar inimigos em hordas

>Hordas são spawnadas uma de cada vez

>Condicionar quando uma horda acaba e passa para outra.

>Contagem de tipos de inimigos que devem ser finaliados para terminar a horda.

*/

namespace adonai {
    class Stage_1_Script : public I_Script<Stage_1>{
        private:
        int8_t qty_enemy_type_1 = 0;
        int8_t qty_enemy_type_2 = 0;
        int8_t qty_enemy_type_3 = 0;

        const int grid_width = bn::sprite_items::spaceship_1.shape_size().width();
        const int grid_height = bn::sprite_items::spaceship_1.shape_size().height();

        enum Stage_State : int8_t {
            Stage_State_NONE    = 0b00000000,
            Stage_State_START   = 0b00000001,
            Stage_State_WAVE_1  = 0b00000010,
            Stage_State_WAVE_2  = 0b00000100,
            Stage_State_WAVE_3  = 0b00001000,
            Stage_State_END     = 0b01111111 //max char u_int8

        };
        Stage_State _state = Stage_State_NONE;
        public:
        
        DataBase_Enemies db_e;
        // esse scripts estão na heap!!!
        Move_And_Destroy_Script wave1_move_n_destroy_script;
        // devem ser deletados depois de usado;
        Move_Enemy_DVD_Script* wave2_medvd_script_1 = new Move_Enemy_DVD_Script;
        Move_Enemy_DVD_Script* wave2_medvd_script_2 = new Move_Enemy_DVD_Script;
        Move_Enemy_DVD_Script* wave2_medvd_script_3 = new Move_Enemy_DVD_Script;
        Move_Enemy_DVD_Script* wave2_medvd_script_4 = new Move_Enemy_DVD_Script;
        Move_Enemy_DVD_Script* wave2_medvd_script_5 = new Move_Enemy_DVD_Script;
        Move_Enemy_DVD_Script* wave2_medvd_script_6 = new Move_Enemy_DVD_Script;

        void start(Stage_1* a) override {
            _state = Stage_State::Stage_State_START;
            //iniciar a primeira horda e contadores
            start_Wave_1();
            _state = Stage_State::Stage_State_WAVE_1;
            // start_Wave_3();
            // _state = Stage_State::Stage_State_WAVE_3;

        };
        
        void update(Stage_1* a) override {
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
                    delete wave2_medvd_script_1;
                    delete wave2_medvd_script_2;
                    delete wave2_medvd_script_3;
                    delete wave2_medvd_script_4;
                    delete wave2_medvd_script_5;
                    delete wave2_medvd_script_6;
                    //start_Wave_3();
                };
                //update_Wave_2();
                break;
            
            case Stage_State::Stage_State_WAVE_3:
                if(finished_Wave_3()){
                    //_state = Stage_State::Stage_State_WAVE_4;
                    //start_Wave_4();
                };
                break;

            // case Stage_State::Stage_State_WAVE_4:
            //     if(finished_Wave_4()){
            //         _state = Stage_State::Stage_State_END;
            //         quit_stage();
            //     };
            //     break;
            
            default:
                BN_LOG("Estado da fase não esperado!");
                break;
            }
            if(_state == Stage_State::Stage_State_WAVE_1 && finished_Wave_1()){
                start_Wave_2();
                _state = Stage_State::Stage_State_WAVE_2;
            };
        };

        private:
        void start_Wave_1(){
            
            //instancias de inimigos
            Enemy* enemy1 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(0+8), (grid_height*(0)) ) );
            enemy1->add_script(wave1_move_n_destroy_script);
            // inimigos na diagonal
            // ------//;
            // -----//;
            // ----<;
            // -----\\;
            // ------\\;
            for (int i = 1; i <= 4; i++) 
            {
                Enemy* enemy2 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(i+8), (grid_height*(i)) ) );
                enemy2->add_script(wave1_move_n_destroy_script);
                Enemy* enemy3 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(i+8), (grid_height*(-1*i)) ) );
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
            Enemy* enemy1 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(8), (grid_height*(-6)) ) );
            enemy1->add_script(*wave2_medvd_script_1);
            Enemy* enemy2 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(8+1), (grid_height*(-6-1)) ) );
            enemy2->add_script(*wave2_medvd_script_2);
            Enemy* enemy3 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(8+2), (grid_height*(-6-2)) ) );
            enemy3->add_script(*wave2_medvd_script_3);

            Enemy* enemy4 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(8), (grid_height*(6)) ) );
            enemy4->add_script(*wave2_medvd_script_4);
            Enemy* enemy5 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(8+1), (grid_height*(6+1)) ) );
            enemy5->add_script(*wave2_medvd_script_5);
            Enemy* enemy6 = db_e.DefaultEnemy(  bn::fixed_point( grid_width*(8+2), (grid_height*(6+2)) ) );
            enemy6->add_script(*wave2_medvd_script_6);

        }

        bool finished_Wave_2(){
            if (ntt_enemies.size()<=0) {   return true; }
            return false;
        }
        void start_Wave_3() {
            Enemy* red = db_e.RedEnemy({0,0});
        }
        bool finished_Wave_3(){
            if (ntt_enemies.size()<=0) {   return true; }
            return false;
        }
        bool stage_1_Clear(){

            return false;
        }

    };
}