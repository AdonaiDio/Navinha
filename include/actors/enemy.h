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
            
        public:
            bn::vector<Enemy*, 20>* ntt_enemies;//referencia da lista de ntts
            bool has_shot = false; //indicativo de que o _shot foi iniciado.
            bn::vector<Shot_Enemy*, 40>* ntt_shots; 

            E_Enemy_State _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
            Shot_Enemy _shot = Shot_Enemy(bn::sprite_items::shoot);
            E_Shot_Type _shot_type = E_Shot_Type::E_Shot_Type_1;
            
            Enemy(  bn::vector<Enemy*, 20>* ntt_e,
                    bn::fixed_point position,  
                    bn::sprite_item sprite_item, 
                    int max_hp);
            Enemy(  bn::vector<Enemy*, 20>* ntt_e,
                    bn::fixed_point position,  
                    bn::sprite_item sprite_item, 
                    int max_hp, 
                    bn::sprite_item shot_sprite_item, 
                    E_Shot_Type shot_type );
            ~Enemy();


            void add_script(I_Script<Enemy>& script);
            void remove_script(I_Script<Enemy>& script);
            // Para associar a lista de ntt_shots presentes na cena que ele foi criado.
            void assign_ntt_shots(bn::vector<Shot_Enemy*, 40>* ntt_shots_ptr){
                ntt_shots = ntt_shots_ptr;
                _shot.ntt_shots = ntt_shots_ptr;
            }

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
            
            //--methods--
            void hit_feedback(){
                is_hitting = true;
                hit_fx = new Hit_FX(_pos, _sprite_item, enemy_anim.current_graphics_index(), is_hitting);
                BN_LOG("is hitting: ", is_hitting);
                BN_LOG("hitFX Usados: ", bn::sprites::used_items_count());
                BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
                BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            }
            void receive_hit();
            // void receive_hit(int index);
            
            void just_delete_this();

            void shoot();
            //retorna true se puder atirar, além de atualizar a lista de disponibilidade dos tiros.
            bool can_shoot();
            void shot_type_1();
            void shot_type_2();
            void shot_type_3();

            void update_collider();
            void update_scripts();
            void update();

            bool can_update();
    };
}