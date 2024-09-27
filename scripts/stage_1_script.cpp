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
//other script embbeded
#include "move_and_destroy_script.cpp"

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
        Move_And_Destroy_Script move_n_destroy_script;

        void start(Stage_1* a) override {
            _state = Stage_State::Stage_State_START;
            //iniciar a primeira horda e contadores
            start_Wave_1();
            _state = Stage_State::Stage_State_WAVE_1;

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
                    //start_Wave_3();
                };
                break;
            
            // case Stage_State::Stage_State_WAVE_3:
            //     if(finished_Wave_3()){
            //         _state = Stage_State::Stage_State_WAVE_4;
            //         start_Wave_4();
            //     };
            //     break;

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
            const int grid_width = bn::sprite_items::spaceship_1.shape_size().width();
            const int grid_height = bn::sprite_items::spaceship_1.shape_size().height();
            //inimigos
            instantiate_default_enemy(  bn::fixed_point( grid_width*(0+8), 
                                                        (grid_height*(0))),
                                        move_n_destroy_script);
                                        
            instantiate_default_enemy(  bn::fixed_point( grid_width*(1+8), 
                                                        (grid_height*(1))),
                                        move_n_destroy_script);
                                        
            instantiate_default_enemy(  bn::fixed_point( grid_width*(2+8), 
                                                        (grid_height*(2))),
                                        move_n_destroy_script);
                                        
            instantiate_default_enemy(  bn::fixed_point( grid_width*(3+8), 
                                                        (grid_height*(3))),
                                        move_n_destroy_script);
                                        
            instantiate_default_enemy(  bn::fixed_point( grid_width*(4+8), 
                                                        (grid_height*(4))),
                                        move_n_destroy_script);
                                        
            instantiate_default_enemy(  bn::fixed_point( grid_width*(1+8), 
                                                        (grid_height*(-1))),
                                        move_n_destroy_script);
                                        
            instantiate_default_enemy(  bn::fixed_point( grid_width*(2+8), 
                                                        (grid_height*(-2))),
                                        move_n_destroy_script);
                                        
            instantiate_default_enemy(  bn::fixed_point( grid_width*(3+8), 
                                                        (grid_height*(-3))),
                                        move_n_destroy_script);
                                        
            instantiate_default_enemy(  bn::fixed_point( grid_width*(4+8), 
                                                        (grid_height*(-4))),
                                        move_n_destroy_script);
        }
        bool finished_Wave_1(){
            //condição para concluir a primeira wave
            //não ter mais inimigos em tela
            if (ntt_enemies.size()<=0) {   return true; }
            return false;
        }

        void start_Wave_2(){ 
            BN_LOG("CHEGOU NA WAVE 2");
        }

        bool finished_Wave_2(){

            return false;
        }

        bool stage_1_Clear(){

            return false;
        }
        
        void instantiate_default_enemy(bn::fixed_point position){
            Enemy* default_enemy = new Enemy( bn::sprite_items::spaceship_1, 
                                        position,
                                        bn::sprite_items::shoot, 
                                        E_Shot_Type::E_Shot_Type_1, 
                                        3);
        }
        void instantiate_default_enemy(bn::fixed_point position, I_Script<Enemy>& script){
            Enemy* default_enemy = new Enemy( bn::sprite_items::spaceship_1,
                                        position,
                                        bn::sprite_items::shoot, 
                                        E_Shot_Type::E_Shot_Type_1, 
                                        3);
            default_enemy->add_script(script);
        }
        
    };
}