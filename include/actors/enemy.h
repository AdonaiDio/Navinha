#pragma once

#include "actor.h"

#include "bn_vector.h"
#include "bn_sprite_animate_actions.h"

#include "shot_enemy.h"

#include "bn_sprite_items_spaceship_1.h"
#include "bn_sprite_items_spaceship_2.h"

namespace adonai
{  
    extern bn::vector<Enemy*, 20> ntt_enemies;

    enum E_Shot_Type{
        E_Shot_Type_1 = 0,
        E_Shot_Type_2 = 2,
        E_Shot_Type_3 = 4
    };
    
    class Enemy : public Actor
    {
        using Actor::Actor;
        protected:
            bool _has_animation;
            
        public:
            Enemy(
                bn::sprite_item sprite_item, 
                bn::fixed_point position,  
                bn::sprite_item shoot_sprite_item, 
                int max_hp = 3);
            ~Enemy();
            //com animação e collider dinâmico
            Enemy(
                bn::sprite_item sprite_item, 
                bn::fixed_point position,  
                bn::sprite_item shoot_sprite_item, 
                bool has_animation,
                const int anim_frames_duration,
                const int anim_frames_count, 
                int max_hp = 3);

            Shot_Enemy _shot;
            
            
            bn::sprite_animate_action<10> enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    0,
                    bn::sprite_items::spaceship_2.tiles_item(),
                    0,0
            );
            bn::sprite_animate_action<10> enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    0,
                    bn::sprite_items::spaceship_2.tiles_item(),
                    0,0
            );
            
            // ponto 1: width+,height0 ; ponto 2: width0,height- ; ponto 3: width-,height0 ;
            // Moveset_1 -> ZigZag 
            //está no lugar errado?
            // const bn::array<bn::fixed_point,3> path_1 = { bn::fixed_point(16*7,(16*1)+8),
            //                                 bn::fixed_point(0, -64+8),
            //                                 bn::fixed_point(-16*7,(16*2)+8) };

            void receive_hit(const int index);
            void shoot();
            void shoot(E_Shot_Type type);

            void update_collider();
            void update();
            
    };
}