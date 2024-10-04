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
        Default_Enemy = 0,
        Red_Enemy = 1
    };

    // Preciso criar um inimigo novo com caracteristicas unicas para cada tipo de inimigo.
    // Depois eu copio esse protótipo para outras instâncias no jogo.
    class DataBase_Enemies{
        public:
        Enemy DefaultEnemy(bn::fixed_point position){
            Enemy default_enemy = Enemy( bn::sprite_items::spaceship_1, 
                                        position,
                                        bn::sprite_items::shoot, 
                                        E_Shot_Type::E_Shot_Type_1, 
                                        3);
            return default_enemy;
        };

        Enemy RedEnemy(bn::fixed_point position){
            Enemy red_enemy = Enemy( bn::sprite_items::spaceship_2, 
                                        position,
                                        bn::sprite_items::shoot, 
                                        E_Shot_Type::E_Shot_Type_1, 
                                        15,7,3);
            return red_enemy;
        };

    };
    

} 

