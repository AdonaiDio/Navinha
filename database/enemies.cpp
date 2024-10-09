//other script embbeded
#pragma once
//butano
#include "bn_sprite_animate_actions.h"
//assets
#include "bn_sprite_items_shoot.h"
#include "bn_sprite_items_spaceship_1.h"
#include "bn_sprite_items_spaceship_2.h"
//my code
#include "enemy.h"
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

        Enemy* DefaultEnemy(bn::fixed_point position){
            Enemy* default_enemy = new Enemy(position);
            return default_enemy;
        };

        Enemy* RedEnemy(bn::fixed_point position){
            Enemy* red_enemy = new Enemy(position,
                                    bn::sprite_items::spaceship_2,
                                    bn::sprite_items::shoot, 
                                    E_Shot_Type::E_Shot_Type_1,  
                                    3);
                                    
            red_enemy->col(bn::rect(    (int)red_enemy->pos().x()-1, 
                                        (int)red_enemy->pos().y()-1, 
                                        10, 14));
            red_enemy->_cols.clear();
            red_enemy->_cols.push_back( { (int)position.x()-1, (int)position.y()-1, 10, 14});
            red_enemy->_cols.push_back( { (int)position.x()-1, (int)position.y()-1, 10, 14});
            red_enemy->_cols.push_back( { (int)position.x()-1, (int)position.y()-1, 10, 12});
            red_enemy->_cols.push_back( { (int)position.x()-1, (int)position.y(),   10, 12});
            red_enemy->_cols.push_back( { (int)position.x()-1, (int)position.y(),   10, 10});
            red_enemy->_cols.push_back( { (int)position.x()-1, (int)position.y(),   10, 12});
            red_enemy->_cols.push_back( { (int)position.x()-1, (int)position.y()-1, 10, 12});

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
    };

} 