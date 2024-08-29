#pragma once

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_rect.h"
#include "bn_vector.h"
#include "bn_sprite_palette_ptr.h"
//#include "bn_sprite_actions.h"

#include "shot_enemy.h"
#include "explosion_fx.h"

#include "bn_sprite_items_spaceship_1.h"
#include "bn_sprite_items_spaceship_2.h"

namespace adonai
{  
    extern bn::vector<Enemy*, 20> ntt_enemies;
    
    class Enemy
    {
        private:
            bn::sprite_ptr _sprite;
            bn::sprite_ptr _sprite_clone;
            bn::fixed_point _pos;
            bn::rect _col = bn::rect( 0, 0, 0, 0 );
            int _hp;
            
            bn::fixed velocity = 1;

            //TODO: testar até onde da para aumentar sem sentir muito delay
            // const int frames_skipped = 5;
            // int frame_counter = 0;

            const int _snake_group; //0:sem grupo; 1:grupo_1; 2... 
            int path_pos_current_index = 0;
            int hit_feedback_duration = 0;
            bn::fixed intensity = 1;
            Explosion_FX* explosion; 
            
        public:
            Enemy(
                bn::sprite_item sprite_item, 
                bn::fixed x, bn::fixed y, 
                bn::sprite_item shoot_sprite_item, 
                int max_hp = 1, int snake_group = 0);
            ~Enemy();
            bool wait_to_destroy = false;

            adonai::Shot_Enemy _shot;
            bn::sprite_ptr sprite();

            bn::fixed_point pos();
            void pos(bn::fixed_point location);

            bn::rect col();

            int hp();
            void hp(int new_value);
    
            // ponto 1: width+,height0 ; ponto 2: width0,height- ; ponto 3: width-,height0 ;
            // Moveset_1 -> ZigZag 
            //está no lugar errado?
            const bn::array<bn::fixed_point,3> path_1 = { bn::fixed_point(16*7,(16*1)+8),
                                            bn::fixed_point(0, -64+8),
                                            bn::fixed_point(-16*7,(16*2)+8) };

            void hit_feedback();
            void receive_hit(const int i);
            void explode();

            void moveset_follow_path(const bn::array<bn::fixed_point,3> &path);

            void identify_snakeGroup();

            void moveset_snake();

            void update_moveset();

            void update();
            
            void update_collider();
    };
}