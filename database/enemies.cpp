//other script embbeded
#pragma once
//butano
#include "bn_sprite_animate_actions.h"
//assets
#include "bn_sprite_items_shoot.h"
#include "bn_sprite_items_shot_3.h"
#include "bn_sprite_items_spaceship_1.h"
#include "bn_sprite_items_spaceship_2.h"
#include "bn_sprite_items_spaceship_3.h"
//my code
#include "enemy.h"
#include "inimigo.h"
//other script embbeded

namespace adonai
{
    enum E_DataBase_Enemies{
        DataBase_DefaultEnemy = 0,
        DataBase_RedEnemy = 1
    };

    // Preciso criar um inimigo novo com caracteristicas unicas para cada tipo de inimigo.
    // A partir do DataBase posso chamar cada um dos inimigos prefabs que retorna um Enemy configurado como deve ser.
    class DataBase_Enemies{
        public:

        // teste de um novo inimigo com optional e etc. Se der certo vira o padrão.
        Inimigo* NovoInimigo(bn::fixed_point position){
            Inimigo* novo_inimigo = new Inimigo(position);
            // não vou inserir na lista de ntt pois ele não é enemy, 
            // ele vai fazer update na cena teste.
            return novo_inimigo;
        }
        //
        
        Enemy* DefaultEnemy(bn::fixed_point position, bn::vector<Enemy*, 20> *ntt_e){
            Enemy* default_enemy = new Enemy(position);
            default_enemy->ntt_enemies = ntt_e;
            default_enemy->ntt_enemies->push_back(default_enemy);
            return default_enemy;
        };

        Enemy* RedEnemy(bn::fixed_point position, bn::vector<Enemy*, 20> *ntt_e){
            Enemy* red_enemy = new Enemy(position,
                                    bn::sprite_items::spaceship_2,
                                    bn::sprite_items::shoot, 
                                    E_Shot_Type::E_Shot_Type_1,  
                                    3);
            red_enemy->ntt_enemies = ntt_e;
            red_enemy->ntt_enemies->push_back(red_enemy);
            red_enemy->col(bn::rect(    (int)red_enemy->pos().x()-1, 
                                        (int)red_enemy->pos().y()-1, 
                                        10, 14));
                                        
            red_enemy->_cols[0] = bn::rect((int)position.x()-1, (int)position.y()-1, 10, 14);
            red_enemy->_cols[1] = bn::rect((int)position.x()-1, (int)position.y()-1, 10, 14);
            red_enemy->_cols[2] = bn::rect((int)position.x()-1, (int)position.y()-1, 10, 12);
            red_enemy->_cols[3] = bn::rect((int)position.x()-1, (int)position.y(),   10, 12);
            red_enemy->_cols[4] = bn::rect((int)position.x()-1, (int)position.y(),   10, 10);
            red_enemy->_cols[5] = bn::rect((int)position.x()-1, (int)position.y(),   10, 12);
            red_enemy->_cols[6] = bn::rect((int)position.x()-1, (int)position.y()-1, 10, 12);

            red_enemy->enemy_anim = bn::create_sprite_animate_action_forever (
                    red_enemy->sprite(),
                    15,
                    bn::sprite_items::spaceship_2.tiles_item(),
                    0,1,2,3,4,5,6
            );
            red_enemy->enemy_clone_anim = bn::create_sprite_animate_action_forever (
                    red_enemy->sprite_clone(),
                    15,
                    bn::sprite_items::spaceship_2.tiles_item(),
                    0,1,2,3,4,5,6
            );

            return red_enemy;
        };

        
        Enemy* PyramidEnemy(bn::fixed_point position, bn::vector<Enemy*, 20> *ntt_e){
            Enemy* pyramid_enemy = new Enemy(position,
                                    bn::sprite_items::spaceship_3,
                                    bn::sprite_items::shot_3, 
                                    E_Shot_Type::E_Shot_Type_3,  
                                    10);
            pyramid_enemy->ntt_enemies = ntt_e;
            pyramid_enemy->ntt_enemies->push_back(pyramid_enemy);
            pyramid_enemy->col(bn::rect((int)pyramid_enemy->pos().x()-1, 
                                        (int)pyramid_enemy->pos().y()+0, 
                                        11, 16));

            pyramid_enemy->enemy_anim = bn::create_sprite_animate_action_forever (
                    pyramid_enemy->sprite(),
                    20,
                    bn::sprite_items::spaceship_3.tiles_item(),
                    0,1,2,3,4,0,0,0,0,0
            );
            pyramid_enemy->enemy_clone_anim = bn::create_sprite_animate_action_forever (
                    pyramid_enemy->sprite_clone(),
                    20,
                    bn::sprite_items::spaceship_3.tiles_item(),
                    0,1,2,3,4,0,0,0,0,0
            );
            return pyramid_enemy;
        };
    };

} 