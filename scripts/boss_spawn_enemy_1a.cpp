#pragma once
//butano
#include <bn_log.h>
//assets
//#include <bn_sprite_items_.h>
//my code
#include <../include/utility.h>
#include "enemy.h"
//this interface
#include <D:/Adonai/My_ROMs/Navinha/scripts/i_script.hpp>
#include "e_spawn_enemy_state.h"

namespace adonai {
    // nave nasce dos fundo de tras do boss
    // as naves se posicionam a frente do boss e vão para sua posição inicial predeterminada
    // depois de posicionadas, em sincronia, as naves voão rápido em linha reta na direção do player.
    // fora da tela são desativadas novamente.
    
    class Boss_Spawn_Enemy_1A_Script : public I_Script<Enemy>{
        private:
            SpawnEnemy_State spawnEnemy_state = SpawnEnemy_State::SPAWNENEMY_NONE_STATE;
            bn::fixed_point _spawn_pos;
            public:
            void start(Enemy* e) override
            {
                e->sprite().set_bg_priority(3);
                spawnEnemy_state = SpawnEnemy_State::SPAWNENEMY_SPAWN_STATE;
                _spawn_pos = e->pos() + bn::fixed_point(16,-16);
                //e->velocity(2);
            };
            
            void update(Enemy* e) override
            {
                //e->pos(move_towards(e->pos(), e->pos()+bn::fixed_point(-1,0), e->velocity()));
                switch (spawnEnemy_state)
                {
                case SpawnEnemy_State::SPAWNENEMY_SPAWN_STATE:
                    e->pos(move_towards(e->pos(), e->pos()+bn::fixed_point(+1,-1), e->velocity()));
                    /* condição de transição */
                    /* chegar na posição final _spawn_pos */
                    if (e->pos().x() >= _spawn_pos.x())
                    {
                        e->sprite().set_bg_priority(1);
                        spawnEnemy_state = SpawnEnemy_State::SPAWNENEMY_REPOSITIONING_STATE;
                    }
                    break;
                
                case SpawnEnemy_State::SPAWNENEMY_REPOSITIONING_STATE:
                    e->pos(move_towards(e->pos(), 
                                        bn::fixed_point(_spawn_pos.x()-56, _spawn_pos.y()-56),
                                        e->velocity()));
                    break;
                
                case SpawnEnemy_State::SPAWNENEMY_ATTACKING_STATE:
                    /* code */
                    break;
                
                case SpawnEnemy_State::SPAWNENEMY_OUTSIDE_STATE:
                    /* code */
                    break;
                case SpawnEnemy_State::SPAWNENEMY_DEAD_STATE:
                    /* code */
                    break;
                
                default:
                    break;
                }
            };
    };
}