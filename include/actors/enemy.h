#pragma once

#include "actor.h"

#include "bn_vector.h"
#include "bn_sprite_animate_actions.h"

#include "shot_enemy.h"

#include "i_script.hpp"

#include "bn_sprite_items_shoot.h"
#include "bn_sprite_items_spaceship_1.h"
#include "bn_sprite_items_spaceship_2.h"

#define MAX_FRAMES_ANIM 10
#define MAX_ENEMY_SHOTS 12

namespace adonai
{  
    namespace GLOBALS
    {
        extern Player* global_player;
    }
    // extern bn::vector<Enemy*, 20> ntt_enemies; 

    enum E_Shot_Type{
        //E_Shot_type_1: tiro comum para frente.
        E_Shot_Type_1 = 0,
        //E_Shot_type_2: tiro triplo, 1 para frente e 2 diagonais.
        E_Shot_Type_2 = 2,
        //E_Shot_type_3: tiro vai para a ultima posição do player ao ser instanciado.
        E_Shot_Type_3 = 4
    };
    
    enum E_Enemy_State{
        E_Enemy_State_NONE = 0,
        E_Enemy_State_MOVING = 2,
        E_Enemy_State_SHOOTING = 4
    };
    
    
    class Enemy : public Actor<Enemy>
    {
        using Actor::Actor;
        private:
            //bool can_update = true;
        protected:
        
        public:
            bn::vector<Enemy*, 20>* ntt_enemies;//referencia da lista de ntts

            Enemy(  bn::fixed_point position = bn::fixed_point(0,0),  
                    bn::sprite_item sprite_item = bn::sprite_items::spaceship_1, 
                    bn::sprite_item shot_sprite_item = bn::sprite_items::shoot, 
                    E_Shot_Type shot_type = E_Shot_Type::E_Shot_Type_1, 
                    int max_hp = 1);
            ~Enemy();

            E_Enemy_State _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
            void add_script(I_Script<Enemy>& script);
            void remove_script(I_Script<Enemy>& script);

            Shot_Enemy _shot;
            bn::array<Shot_Enemy, MAX_ENEMY_SHOTS> _shots;
            //true se shot tiver disponível
            bn::array<bool*, MAX_ENEMY_SHOTS> _shots_is_available;
            
            E_Shot_Type _shot_type = E_Shot_Type::E_Shot_Type_1;


            //_cols é uma lista de colliders 1 para cada frame do spritesheet
            bn::array<bn::rect, MAX_FRAMES_ANIM> _cols;

            bn::sprite_animate_action<MAX_FRAMES_ANIM> enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    0,
                    bn::sprite_items::spaceship_2.tiles_item(),
                    0,0
            );
            bn::sprite_animate_action<MAX_FRAMES_ANIM> enemy_clone_anim = 
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
            void just_delete_this();

            void shoot();
            bool can_shoot();//retorna true se puder atirar, além de atualizar a lista de disponibilidade dos tiros.
            void shot_type_1();
            void shot_type_2();
            void shot_type_3();

            void update_collider();
            void update_scripts();
            void update_all_shots_occupied();
            void update();

            bool all_shots_available();

            bool can_update();
    };
}