#pragma once

#include "actor.h"

#include "bn_vector.h"
//#include "bn_sprite_actions.h"

#include "shot_enemy.h"

#include "bn_sprite_items_spaceship_1.h"
#include "bn_sprite_items_spaceship_2.h"

namespace adonai
{  
    extern bn::vector<Enemy*, 20> ntt_enemies;
    
    class Enemy : public Actor
    {
        using Actor::Actor;
        protected:

            const int _snake_group; //0:sem grupo; 1:grupo_1; 2... 
            int path_pos_current_index = 0;
            
        public:
            Enemy(
                bn::sprite_item sprite_item, 
                bn::fixed_point position,  
                bn::sprite_item shoot_sprite_item, 
                int max_hp = 3, int snake_group = 0);
            ~Enemy();


            adonai::Shot_Enemy _shot;
            
    
            // ponto 1: width+,height0 ; ponto 2: width0,height- ; ponto 3: width-,height0 ;
            // Moveset_1 -> ZigZag 
            //está no lugar errado?
            const bn::array<bn::fixed_point,3> path_1 = { bn::fixed_point(16*7,(16*1)+8),
                                            bn::fixed_point(0, -64+8),
                                            bn::fixed_point(-16*7,(16*2)+8) };


            void moveset_follow_path(const bn::array<bn::fixed_point,3> &path);

            void identify_snakeGroup();

            void moveset_snake();

            void update_moveset();
            
            void receive_hit(const int index);

            void update_collider();
            void update();
            
    };
}